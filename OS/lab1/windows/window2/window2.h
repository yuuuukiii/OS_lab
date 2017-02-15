#ifndef WINDOW2_H
#define WINDOW2_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>

namespace Ui {
class window2;
}

class window2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit window2(QWidget *parent = 0);
    ~window2();

private slots:
    void on_pushButton_clicked();

private:
    Ui::window2 *ui;
    QTimer *timer;
    QLabel* label;
public slots:
    void onTimerOut();
public:
    int number;
};

#endif // WINDOW2_H
