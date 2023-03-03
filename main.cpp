#include "overlay.h"
#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Overlay overlay;

    overlay.setAttribute(Qt::WA_NoSystemBackground, true);
    overlay.setAttribute(Qt::WA_TranslucentBackground, true);
    overlay.setAttribute(Qt::WA_TransparentForMouseEvents, true);
    overlay.setWindowFlags(Qt::FramelessWindowHint);
    overlay.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    overlay.showFullScreen();

    Menu menu;
    menu.setAttribute(Qt::WA_TransparentForMouseEvents, false);
    menu.setAttribute(Qt::WA_NoSystemBackground, true);
    menu.setAttribute(Qt::WA_TranslucentBackground, true);
    menu.setWindowFlags(Qt::FramelessWindowHint);
    menu.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    menu.show();

    return application.exec();
}
