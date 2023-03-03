#ifndef OVERLAY_H
#define OVERLAY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Overlay; }
QT_END_NAMESPACE

class Overlay : public QMainWindow
{
    Q_OBJECT

public:
    Overlay(QWidget *parent = nullptr);
    ~Overlay();

private:
    Ui::Overlay *ui;
};
#endif // OVERLAY_H
