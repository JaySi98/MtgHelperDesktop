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

void ViewCardSearch::button_search_pressed()
{
    // TODO
}

void ViewCardSearch::button_advanced_pressed()
{
    // TODO
}

void ViewCardSearch::create_widgets()
{
    // widgets setup
    button_search = new QPushButton(main_widget);
    button_search->setText("Search");
    connect(button_search, &QPushButton::pressed, this, &ViewCardSearch::button_search_pressed);

    button_advanced = new QPushButton(main_widget);
    button_advanced->setText("Advanced");
    connect(button_advanced, &QPushButton::pressed, this, &ViewCardSearch::button_advanced_pressed);

    box_card_search = new QGroupBox(main_widget);
    box_card_search->setTitle("Search List");

    box_card_info = new QGroupBox(main_widget);
    box_card_info->setTitle("Card Info");

    info_scroll_area = new QScrollArea(main_widget);
    list_widget = new QListWidget(main_widget);
    search_line = new QLineEdit(main_widget);

    // layout setup
    central_layout = new QHBoxLayout(main_widget);
    button_layout = new QHBoxLayout(main_widget);
    button_layout->addWidget(search_line);
    button_layout->addWidget(button_search);
    button_layout->addWidget(button_advanced);

    list_layout = new QVBoxLayout(main_widget);
    list_layout->addLayout(button_layout);
    list_layout->addWidget(list_widget);
    box_card_search->setLayout(list_layout);

    info_layout = new QVBoxLayout(main_widget);
    info_layout->addWidget(info_scroll_area);
    box_card_info->setLayout(info_layout);

    central_layout->addWidget(box_card_search);
    central_layout->addWidget(box_card_info);
    central_layout->setStretch(0,4);
    central_layout->setStretch(1,6);
}
