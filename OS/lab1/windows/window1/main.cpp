#include "window1.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window1 w;
    w.move(200, 200);
    w.show();
    return a.exec();
}
