#include "ViewCardSearch.h"

ViewCardSearch::ViewCardSearch(QObject *parent)
    : View{parent}
{
    create_widgets();
}

ViewCardSearch::~ViewCardSearch()
{
    delete main_widget;
}

void ViewCardSearch::button_pressed()
{
    qDebug() << "ViewCardSearch: button pressed";
    emit signal();
}

void ViewCardSearch::create_widgets()
{
    central_layout = new QVBoxLayout(main_widget);
    button         = new QPushButton(main_widget);
    box            = new QGroupBox(main_widget);
    box_layout     = new QVBoxLayout(box);

    connect(button, &QPushButton::pressed, this, &ViewCardSearch::button_pressed);

    box_layout->addWidget(button);
    box->setLayout(box_layout);
    central_layout->addWidget(box);
}
