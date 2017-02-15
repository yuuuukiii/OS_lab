#include "window2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window2 w;
    w.move(600, 200);
    w.show();

    return a.exec();
}
