#include "window1.h"
#include "ui_window1.h"
#include <time.h>
window1::window1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window1)
{
    ui->setupUi(this);
    label = ui->label_2;
    //init
    time_t timep;
    time(&timep);
    label->setText(ctime(&timep));
    //set QTimer to update
    timer = new QTimer();
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

window1::~window1()
{
    delete ui;
}

void window1::on_pushButton_clicked()
{
     QCoreApplication::quit();
}
void window1::onTimerOut()
{
    time_t timep;
    time(&timep);
    label->setText(ctime(&timep));
}
