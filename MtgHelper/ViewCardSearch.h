#ifndef VIEWCARDSEARCH_H
#define VIEWCARDSEARCH_H

#include <QObject>
#include <QPushButton>
#include <QGroupBox>
#include <QLayout>
#include <View.h>

class ViewCardSearch : public View
{
    Q_OBJECT
public:
    explicit ViewCardSearch(QObject *parent = nullptr);
    ~ViewCardSearch();

public slots:
    void button_pressed();

private:
    QPushButton* button;
    QGroupBox*   box;
    QVBoxLayout* central_layout;
    QVBoxLayout* box_layout;

    void create_widgets();
};

#endif // VIEWCARDSEARCH_H
