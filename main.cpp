#include "overlay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Overlay w;
    w.show();
    return a.exec();
}
