#include "ViewCardSearch.h"

ViewCardSearch::ViewCardSearch(QObject *parent)
    : View{parent}
    , controller(QSharedPointer<ControllerCardSearch>(new ControllerCardSearch()))
    , card_details(nullptr)
{
    connect(controller.get(), &ControllerCardSearch::card_list_fetched,    this,              &ViewCardSearch::set_card_list);
    connect(controller.get(), &ControllerCardSearch::card_details_fetched, this,              &ViewCardSearch::set_card_details);
    connect(this,             &ViewCardSearch::card_list_request,          controller.get(),  &ControllerCardSearch::get_card_list);
    connect(this,             &ViewCardSearch::card_details_request,       controller.get(),  &ControllerCardSearch::get_card_details);

    create_main_widget();
}

ViewCardSearch::~ViewCardSearch()
{
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
    card_details = QSharedPointer<QWidget>(create_card_details_widget(card));
    info_scroll_area->setWidget(card_details.get());
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

    info_scroll_area = new QScrollArea(main_widget);
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

QWidget* ViewCardSearch::create_card_details_widget(Card* card)
{
    QWidget* card_details_widget = new QWidget;

    QLabel* card_image = new QLabel(card_details_widget);
    card_image->setPixmap(card->details[SIDE_FACE].image);

    QVBoxLayout* main_layout = new QVBoxLayout(card_details_widget);
    main_layout->addWidget(card_image);
    main_layout->addWidget(new QLabel(card->details[SIDE_FACE].name, card_details_widget));
    main_layout->addWidget(new QLabel(card->details[SIDE_FACE].typeLine, card_details_widget));
    main_layout->addWidget(new QLabel(card->details[SIDE_FACE].manaCost, card_details_widget));

    QPlainTextEdit* card_text = new QPlainTextEdit(card_details_widget);
    card_text->appendPlainText(card->details[SIDE_FACE].text);
    card_text->setReadOnly(true);
    card_text->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    main_layout->addWidget(card_text);

    if(card->details[SIDE_FACE].cardType & CARD_TYPE_CREATURE || card->details[SIDE_FACE].cardType & CARD_TYPE_PLANESWALKER )
        main_layout->addWidget(new QLabel(card->details[SIDE_FACE].stats, card_details_widget));

    main_layout->addWidget(new QLabel(card->rarity, card_details_widget));
    main_layout->addWidget(new QLabel(card->setName, card_details_widget));

    return card_details_widget;
}
