#include "View.h"

View::View(QObject *parent)
    : QObject{parent}
    , main_widget(new QWidget())
{ }

QWidget* View::get_widget()
{
    return main_widget;
}
