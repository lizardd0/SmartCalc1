#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_bracket_left, SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_bracket_right, SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_power, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers() {
    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_label;

    if (ui->lineEdit->text().contains(".") && button->text() == "0") {
        new_label = ui->lineEdit->text() + button->text();
    } else {
        all_numbers = (ui->lineEdit->text() + button->text()).toDouble();
        new_label = QString::number(all_numbers, 'g', 15);  // перевод all_numbers double to str
    }

    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
//    ui->lineEdit_X->setText(ui->lineEdit_X->text() + button->text());
}

void MainWindow::on_pushButton_dot_clicked() {
        ui->lineEdit->setText(ui->lineEdit->text() + "."); // вывод точки в ui
}

void MainWindow::operations() {
    QPushButton *button = (QPushButton *)sender();

    QString new_label;

    new_label = ui->lineEdit->text();

    if (button->text() == "/" && !(ui->lineEdit->text().endsWith("/")) && !(ui->lineEdit->text().endsWith("/"))) {
        new_label += "/";
    } else if (button->text() == "*" && !(ui->lineEdit->text().endsWith("*")) && !(ui->lineEdit->text().endsWith("*"))) {
        new_label += "*";
    } else if (button->text() == "+" && !(ui->lineEdit->text().endsWith("+"))) {
        new_label += "+";
    } else if (button->text() == "-" && !(ui->lineEdit->text().endsWith("-"))) {
        new_label += "-";
    } else if (button->text() == "^" && !(ui->lineEdit->text().endsWith("^"))) {
        new_label += "^";
    } else if (button->text() == "mod" && !(ui->lineEdit->text().endsWith("mod"))) {
        new_label += "mod";
    } else if (button->text() == "(") {
        new_label += "(";
    } else if (button->text() == ")") {
        new_label += ")";
    }

     ui->lineEdit->setText(ui->lineEdit->text() + button->text());
}


void MainWindow::functions() {
    QPushButton *button = (QPushButton *)sender();

    QString new_label;

    new_label = ui->lineEdit->text() + button->text();

    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
}



void MainWindow::on_pushButton_equal_clicked() {
    QString output;
        double result;
        xValue = ui->lineEdit_X->text().toDouble();
        int check = smart_calculator((char*)ui->lineEdit->text().toStdString().c_str(), xValue, &result);
        if (!check) {
            output = QString::number(result, 'g', 8);
            ui->lineEdit->setText(output);
        } else {
            if (check == 1)
                ui->lineEdit->setText("incorrect data");
            else
                ui->lineEdit->setText("division by zero");
        }
}

void MainWindow::on_pushButton_clear_clicked() {
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_multiply->setChecked(false);

    ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_X_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text() + "x");
}

void MainWindow::on_pushButton_makeGraph_clicked()
{
    ui->widget_graph->clearGraphs();

    hz = 0.1;
    xstart = ui->doubleSpinBox_x_2->value();
    xfinish = ui->doubleSpinBox_x->value();

    ui->widget_graph->xAxis->setRange(ui->doubleSpinBox_x_2->value(), ui->doubleSpinBox_x->value());
    ui->widget_graph->yAxis->setRange(ui->doubleSpinBox_y_2->value(), ui->doubleSpinBox_y->value());

    N = (xfinish-xstart)/hz+2;

    for (X = xstart; X <= xfinish; X += hz) {
        smart_calculator((char*)ui->lineEdit->text().toStdString().c_str(), X, &Y);
        x.push_back(X);
        y.push_back(Y);
    }

    ui->widget_graph->addGraph();
    ui->widget_graph->graph(0)->addData(x, y);
    ui->widget_graph->replot();
    x.clear();
    y.clear();
}


void MainWindow::on_radioButton_type1_clicked()
{
     data->type = 0;
}


void MainWindow::on_radioButton_type2_clicked()
{
     data->type = 1;
}


void MainWindow::on_pushButton_count_clicked()
{
    data->creditsum = ui->spinBox_Summa->value();
       data->term = ui->spinBox_duration->value();
       data->percent = ui-> spinBox_percas->value();
       credit_calculator(data);
       if (data->type)
           ui->textEdit_payment->setText(QString::number(data->monthpay[0], 'f', 2) + " → \n" + QString::number(data->monthpay[(int)data->term-1], 'f', 2));
       else
           ui->textEdit_payment->setText(QString::number(data->monthpay[0], 'f', 2));
       ui->textEdit_overpay->setText(QString::number(data->overpayment, 'f', 2));
       ui->textEdit_total->setText(QString::number(data->total, 'f', 2));
}


void MainWindow::on_pushButton_dep_count_clicked()
{
    v.dsum = ui->doubleSpinBox_summa->value();
        v.term = ui->doubleSpinBox_duration->value();
        v.percent = ui->doubleSpinBox_perc->value();
        v.taxrate = ui->doubleSpinBox_taxrate->value();
        v.replenish_list[0] = ui->doubleSpinBox_addMoney->value();
        v.withdraw_list[0] = ui->doubleSpinBox_takeMoney->value();

        deposit_calculator(&v);
        ui->textEdit->setFontPointSize(18);
        ui->textEdit->setText("Начисленные прoценты");
        ui->textEdit_2->setText(QString::number(v.apercent, 'f', 2));
        ui->textEdit_3->setFontPointSize(18);
        ui->textEdit_3->setText("Налог");
        ui->textEdit_4->setText(QString::number(v.taxsum, 'f', 2));
        ui->textEdit_5->setFontPointSize(18);
        ui->textEdit_5->setText("Сумма на вкладе к концу срока");
        ui->textEdit_7->setText(QString::number(v.total, 'f', 2));
}


void MainWindow::on_radioButton_month_clicked()
{
    v.period = 1;
}


void MainWindow::on_radioButton_qurtal_clicked()
{
    v.period = 3;
}


void MainWindow::on_radioButton_halfyear_clicked()
{
    v.period = 6;
}


void MainWindow::on_radioButton_year_clicked()
{
    v.period = 12;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked) {
        v.capitalization = 1;
    } else {
        v.capitalization = 0;
    }
}

