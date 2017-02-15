#include "window3.h"
#include "ui_window3.h"
#include <stdio.h>
window3::window3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window3)
{
    ui->setupUi(this);
    l_sum = ui->sum;
    l_num = ui->num;
    sum = 0;
    num = 1;

    l_sum->setText("0");
    l_num->setText("1");
    timer = new QTimer();
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

window3::~window3()
{
    delete ui;
}
void window3::on_pushButton_clicked()
{
    QCoreApplication::quit();
}
void window3::onTimerOut()
{
    sum = (num == 1000)?(sum):(sum+num);
    num = (num == 1000)?(num):(num+1);
    char t[10];
    sprintf(t, "%d", sum);
    l_sum->setText(t);
    sprintf(t, "%d", num);
    l_num->setText(t);

}

