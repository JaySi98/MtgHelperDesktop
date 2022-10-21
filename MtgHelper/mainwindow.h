#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSharedPointer>

#include "apiconnector.h"
#include "card.h"
#include "carddetailsview.h"
#include <ViewCardSearch.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void SearchButtonPressed();
    void ListItemPressed();
    void addCardToRemembered(Card* card);
    void SetCardsList(QStringList);
    void SetCardsDetails(Card* card);
    void SetCardImage(QPixmap image);

    void set_card_serch_view();

private:
    Ui::MainWindow *ui;
    APIConnector* apiConnector;

    QList<QSharedPointer<View>> view_list;
    QList<QSharedPointer<Card>> cardsRememberd;
    QSharedPointer<Card>        currentCard;
    QSharedPointer<QWidget>     p_card_details_view;

};
#endif // MAINWINDOW_H
