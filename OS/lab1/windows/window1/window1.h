#ifndef WINDOW1_H
#define WINDOW1_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
namespace Ui {
class window1;
}

class window1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit window1(QWidget *parent = 0);
    ~window1();

private slots:
    void on_pushButton_clicked();
public slots:
    void onTimerOut();

private:
    Ui::window1 *ui;
    QTimer *timer;
    QLabel* label;
};

#endif // WINDOW1_H
