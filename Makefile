CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
SOURCES=SmartCalc.c 
OBJECTS=$(SOURCES:.c=.o)
OS = $(shell uname)
TEST_FILE_NAME = CalcTest.c

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

all: gcov_report install

install: uninstall
		mkdir build
		cd build && cmake build ../cpp_dir
		make -C ./build
		open ./build/CalcUI.app/Contents/MacOs/CalcUi

uninstall:
		rm -rf build/
		rm -rf Calc.tar

dist:
		tar -cf ./Calc.tar ./build/CalcUI.app/Contents/MacOs/CalcUi

SmartCalc.a: clean $(OBJECTS)
	ar -rcs SmartCalc.a $(OBJECTS)
	rm -f *.o

tests: $(TEST_FILE_NAME) SmartCalc.a
	$(CC) $(CFLAGS) $(TEST_FILE_NAME) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

gcov_report: tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

dvi: 
	open ReadMe.md

clean:
	make uninstall
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt test.info test.dSYM *.tar

# install lcov:
# 	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
# 	brew install lcov

check: tests
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h *.c
	rm -rf CPPLINT.cfg
	make test
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif