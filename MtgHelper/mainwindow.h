#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apiconnector.h"
#include "carddetailsview.h"
#include "card.h"

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
    void SearchForCards();
    void SearchForCardDetails();
    void SetCardsList(QStringList);
    void SetCardsDetails(Card card);
    void SetCardImage(QPixmap image);

private:
    Ui::MainWindow *ui;
    APIConnector* apiConnector;
    CardDetailsView* cardDetailsView;
};
#endif // MAINWINDOW_H


