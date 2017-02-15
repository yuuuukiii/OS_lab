#ifndef WINDOW3_H
#define WINDOW3_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
namespace Ui {
class window3;
}

class window3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit window3(QWidget *parent = 0);
    ~window3();

private:
    Ui::window3 *ui;
    QTimer *timer;
    QLabel* l_sum;
    QLabel* l_num;
    int sum;
    int num;
public slots:
    void onTimerOut();
public:

private slots:
    void on_pushButton_clicked();
};
#endif // WINDOW3_H
