#include "window2.h"
#include "ui_window2.h"
#include <stdio.h>
window2::window2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window2)
{
    ui->setupUi(this);
    label = ui->label;
    label->setText("0");
    timer = new QTimer();
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

window2::~window2()
{
    delete ui;
}

void window2::on_pushButton_clicked()
{
    QCoreApplication::quit();
}
void window2::onTimerOut()
{
    number = (number+1)%10;
    char t[4];
    sprintf(t, "%d", number);
    label->setText(t);
}
