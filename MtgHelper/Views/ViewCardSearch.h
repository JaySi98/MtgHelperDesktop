#ifndef VIEWCARDSEARCH_H
#define VIEWCARDSEARCH_H

#include <QObject>
#include <QPushButton>
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QScrollArea>
#include <Views/View.h>

class ViewCardSearch : public View
{
    Q_OBJECT
public:
    explicit ViewCardSearch(QObject *parent = nullptr);
    ~ViewCardSearch();

public slots:
    void button_search_pressed();
    void button_advanced_pressed();

private:
    QHBoxLayout* central_layout;
    QHBoxLayout* button_layout;
    QVBoxLayout* list_layout;
    QVBoxLayout* info_layout;

    QPushButton* button_search;
    QPushButton* button_advanced;
    QGroupBox*   box_card_search;
    QGroupBox*   box_card_info;
    QScrollArea* info_scroll_area;
    QListWidget* list_widget;
    QLineEdit*   search_line;

    void create_widgets();
};

#endif // VIEWCARDSEARCH_H
