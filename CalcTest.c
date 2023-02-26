#include <check.h>
#include <math.h>
#include "SmartCalc.h"

double res = 0.0;

START_TEST(sum) {
    char str[256] = "21.21+15.15";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(21.21 + 15.15, res);
}
END_TEST

START_TEST(substraction) {
    char str[256] = "21.21-15.15";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(21.21 - 15.15, res);
}
END_TEST

START_TEST(multiplication1) {
    char str[256] = "21.21*15.15";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(21.21 * 15.15, res);
}
END_TEST

START_TEST(division) {
    char str[256] = "21.21/15.15";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(21.21 / 15.15, res);
}
END_TEST

START_TEST(mod1) {
    char str[256] = "21.21mod15.15";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(fmod(21.21, 15.15), res);
}
END_TEST

START_TEST(pow1) {
    char str[256] = "21.21^15.15";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(powf(21.21, 15.15), res);
}
END_TEST

START_TEST(x) {
    char str[256] = "x+5";
    smart_calculator(str, 3.14, &res);
    ck_assert_double_eq(5 + 3.14, res);
}
END_TEST

START_TEST(simple_1) {
    char str[256] = "15*(9-20)";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(15*(9-20), res);
}
END_TEST

START_TEST(simple_2) {
    char str[256] = "(3.17+8.18)-5(2.65-7.87)";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(((3.17+8.18)-5*(2.65-7.87)), res);
}
END_TEST

START_TEST(sinus) {
    char str[256] = "sin((3.17+8.18)-5(2.65-7.87))";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(sin((3.17+8.18)-5*(2.65-7.87)), res);
}
END_TEST

START_TEST(cosinus) {
    char str[256] = "cos((3.17+8.18)-5(2.65-7.87))";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(cos((3.17+8.18)-5*(2.65-7.87)), res);
}
END_TEST

START_TEST(tangens) {
    char str[256] = "tan((3.17+8.18)-5(2.65-7.87))";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(tan((3.17+8.18)-5*(2.65-7.87)), res);
}
END_TEST

START_TEST(arcsinus) {
    char str[256] = "asin(45*0.0001)";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(asin(45*0.0001), res);
}
END_TEST

START_TEST(arccosinus) {
    char str[256] = "acos(45*0.0001)";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(acos(45*0.0001), res);
}
END_TEST

START_TEST(arctangens) {
    char str[256] = "atan(45*0.01)";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(atan(45*0.01), res);
}
END_TEST

START_TEST(log10_test) {
    char str[256] = "log((3.17+8.18)-5(2.65-7.87))";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(log10((3.17+8.18)-5*(2.65-7.87)), res);
}
END_TEST

START_TEST(ln) {
    char str[256] = "ln((3.17+8.18)-5(2.65-7.87))";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(log((3.17+8.18)-5*(2.65-7.87)), res);
}
END_TEST

START_TEST(sqrt_test) {
    char str[256] = "sqrt((3.17+8.18)-5(2.65-7.87))";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(sqrt((3.17+8.18)-5*(2.65-7.87)), res);
}
END_TEST

START_TEST(difficult_expression) {
    char str[256] = "ln((3.17+8.18)-5(2.65-7.87))*sqrt(1.15-0.04)+15acos(0.02+0.03)";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq((log((3.17+8.18)-5*(2.65-7.87))*sqrt(1.15-0.04)+15*acos(0.02+0.03)), res);
}
END_TEST

START_TEST(pls) {
    char str[256] = "cos(5)*sqrt(34+8.8)+8";
    smart_calculator(str, 0.0, &res);
    ck_assert_double_eq(cos(5)*sqrt(34+8.8)+8, res);
}

START_TEST(errors) {

    int error = 0;
    char str[256] = "blablabla";
    error = smart_calculator(str, 0.0, &res);
    ck_assert_int_eq(error, 1);

   
    error = 0;
    char str1[256] = "15+-16";
    error = smart_calculator(str1, 0.0, &res);
    ck_assert_int_eq(error, 1);


    error = 0;
    char str2[256] = "2+4.267.244";
    error = smart_calculator(str2, 0.0, &res);
    ck_assert_int_eq(error, 1);

    error = 0;
    char str3[256] = "-mod16";
    error = smart_calculator(str3, 0.0, &res);
    ck_assert_int_eq(error, 1);


    error = 0;
    char str4[256] = "sqqrt(24)";
    error = smart_calculator(str4, 0.0, &res);
    ck_assert_int_eq(error, 1);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, sum);
    tcase_add_test(tc1_1, substraction);
    tcase_add_test(tc1_1, multiplication1);
    tcase_add_test(tc1_1, division);
    tcase_add_test(tc1_1, mod1);
    tcase_add_test(tc1_1, pow1);
    tcase_add_test(tc1_1, x);
    tcase_add_test(tc1_1, simple_1);
    tcase_add_test(tc1_1, simple_2);
    tcase_add_test(tc1_1, sinus);
    tcase_add_test(tc1_1, cosinus);
    tcase_add_test(tc1_1, tangens);
    tcase_add_test(tc1_1, arcsinus);
    tcase_add_test(tc1_1, arccosinus);
    tcase_add_test(tc1_1, arctangens);
    tcase_add_test(tc1_1, log10_test);
    tcase_add_test(tc1_1, ln);
    tcase_add_test(tc1_1, sqrt_test);
    tcase_add_test(tc1_1, difficult_expression);
    tcase_add_test(tc1_1, errors);
    tcase_add_test(tc1_1, pls);

    srunner_run_all(sr, CK_ENV);
    srunner_ntests_failed(sr);
    srunner_free(sr);

    return (0);
}
