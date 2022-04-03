#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apiconnector.h"
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
    void SetCardsList(QList<Card>* cardList);
    void SetCardsDetails(Card card);

private:
    Ui::MainWindow *ui;
    APIConnector* apiConnector;
};
#endif // MAINWINDOW_H


