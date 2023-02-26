#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <qcustomplot.h>
#include <QVector>

#ifdef __cplusplus
extern "C" {
#endif
#include "../SmartCalc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
//    void keyPressEvent(QKeyEvent *e) override;

private:
    Ui::MainWindow *ui;
        double xstart, xfinish, hz, X, Y;
        int N;
        QVector <double> x, y;
        double xValue;

        credit_calc d;
        credit_calc *data = &d;

        deposit_calc v;

private slots:
    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operations();
    void functions();
    void on_pushButton_equal_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_X_clicked();
    void on_pushButton_makeGraph_clicked();
    void on_radioButton_type1_clicked();
    void on_radioButton_type2_clicked();
    void on_pushButton_count_clicked();
    void on_pushButton_dep_count_clicked();
    void on_radioButton_month_clicked();
    void on_radioButton_qurtal_clicked();
    void on_radioButton_halfyear_clicked();
    void on_radioButton_year_clicked();
    void on_checkBox_clicked(bool checked);
};


#endif // MAINWINDOW_H
