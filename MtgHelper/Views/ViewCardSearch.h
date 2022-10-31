#ifndef VIEWCARDSEARCH_H
#define VIEWCARDSEARCH_H

#include <QObject>
#include <QPushButton>
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QScrollArea>
#include <QSharedPointer>
#include <QLabel>
#include <QPlainTextEdit>
#include <Views/View.h>
#include <Controllers/ControllerCardSearch.h>
#include <Api/Card.h>

class ViewCardSearch : public View
{
    Q_OBJECT
public:
    explicit ViewCardSearch(QObject *parent = nullptr);
    ~ViewCardSearch();

signals:
    void card_list_request(QString query);
    void card_details_request(QString card_name);

public slots:
    void button_search_pressed();
    void button_advanced_pressed();
    void list_item_pressed();
    
    void set_card_list(QStringList card_list);
    void set_card_details(Card* card);
    void flip_image();

private:
    QHBoxLayout* central_layout;
    QHBoxLayout* button_layout;
    QVBoxLayout* list_layout;
    QVBoxLayout* info_layout;
    QPushButton* button_search;
    QPushButton* button_advanced;
    QGroupBox*   box_card_search;
    QGroupBox*   box_card_info;
    QListWidget* list_widget;
    QLineEdit*   search_line;

    QLabel*      card_image;
    QPushButton* button_collection;
    QPushButton* button_watchlist;
    QPushButton* button_flip;

    QSharedPointer<ControllerCardSearch> controller;
    QSharedPointer<QWidget> card_details;
    int current_side;

    void     create_main_widget();
    QWidget* create_card_details_widget(Card* card);
};

#endif // VIEWCARDSEARCH_H
