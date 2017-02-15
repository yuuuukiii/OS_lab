#include "window3.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window3 w;
    w.move(1000, 200);
    w.show();

    return a.exec();
}
