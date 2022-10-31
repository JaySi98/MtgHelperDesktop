#include "ViewCardSearch.h"

ViewCardSearch::ViewCardSearch(QObject *parent)
    : View{parent}
    , controller(QSharedPointer<ControllerCardSearch>(new ControllerCardSearch()))
    , card_details(nullptr)
    , current_side(SIDE_FACE)
{
    connect(controller.get(), &ControllerCardSearch::card_list_fetched,    this,              &ViewCardSearch::set_card_list);
    connect(controller.get(), &ControllerCardSearch::card_details_fetched, this,              &ViewCardSearch::set_card_details);
    connect(this,             &ViewCardSearch::card_list_request,          controller.get(),  &ControllerCardSearch::get_card_list);
    connect(this,             &ViewCardSearch::card_details_request,       controller.get(),  &ControllerCardSearch::get_card_details);

    create_main_widget();
}

ViewCardSearch::~ViewCardSearch()
{
    card_details.clear();
    delete main_widget;
}

void ViewCardSearch::button_search_pressed()
{
    list_widget->clear();
    QString query = search_line->text();

    emit card_list_request(query);
}

void ViewCardSearch::button_advanced_pressed()
{
    // TODO
}

void ViewCardSearch::list_item_pressed()
{
    QString card_name = list_widget->currentItem()->text();
    emit card_details_request(card_name);
}

void ViewCardSearch::set_card_list(QStringList card_list)
{
    list_widget->addItems(card_list);
}

void ViewCardSearch::set_card_details(Card* card)
{
    card_details.clear();
    current_side = SIDE_FACE;
    card_details = QSharedPointer<QWidget>(create_card_details_widget(card));

    info_layout->addWidget(card_details.get());
}

void ViewCardSearch::flip_image()
{
    if(current_side == SIDE_FACE)
    {
        current_side = SIDE_BACK;
    }
    else
    {
        current_side = SIDE_FACE;
    }

    QPixmap flip_image = controller->get_card_flip_image(current_side);
    card_image->setPixmap(flip_image);
}

void ViewCardSearch::create_main_widget()
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

    list_widget = new QListWidget(main_widget);
    connect(list_widget, &QListWidget::itemPressed, this, &ViewCardSearch::list_item_pressed);

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
    box_card_info->setLayout(info_layout);

    central_layout->addWidget(box_card_search);
    central_layout->addWidget(box_card_info);
    central_layout->setStretch(0,4);
    central_layout->setStretch(1,6);
}

QWidget* ViewCardSearch::create_card_details_widget(Card* card)
{    
    QWidget* card_details_widget = new QWidget;

    card_image = new QLabel(card_details_widget);
    card_image->setPixmap(card->get_image(current_side));

    QScrollArea* info_scroll_area = new QScrollArea(card_details_widget);
    info_scroll_area->setWidget(card_image);

    button_collection = new QPushButton(card_details_widget);
    button_collection->setText("Add to collection");
    connect(button_collection, &QPushButton::pressed, controller.get(), &ControllerCardSearch::add_card_to_collection);

    button_watchlist = new QPushButton(card_details_widget);
    button_watchlist->setText("Add to watchlist");
    connect(button_watchlist, &QPushButton::pressed, controller.get(), &ControllerCardSearch::add_card_to_watchlist);

    QVBoxLayout* main_layout = new QVBoxLayout(card_details_widget);
    main_layout->addWidget(info_scroll_area);

    if(card->isDual)
    {
        button_flip = new QPushButton(card_details_widget);
        button_flip->setText("Flip");
        connect(button_flip, &QPushButton::pressed, this, &ViewCardSearch::flip_image);
        main_layout->addWidget(button_flip);
    }
    main_layout->addWidget(button_collection);
    main_layout->addWidget(button_watchlist);

    return card_details_widget;
}
