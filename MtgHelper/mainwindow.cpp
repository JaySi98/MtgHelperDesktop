#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    apiConnector = new APIConnector();

    connect(ui->buttonSearch,   &QToolButton::pressed,          this, &MainWindow::SearchForCards);
    connect(ui->resultList,     &QListWidget::itemPressed,      this, &MainWindow::SearchForCardDetails);
    connect(apiConnector,       &APIConnector::CardListRead,    this, &MainWindow::SetCardsList);
    connect(apiConnector,       &APIConnector::CardDetailsRead, this, &MainWindow::SetCardsDetails);
}

MainWindow::~MainWindow()
{
    delete apiConnector;
    delete ui;
}

void MainWindow::SearchForCards()
{
    //TODO budowanie query
    apiConnector->GetReply(REQUEST_CARD_LIST, "search?unique&q=c%3Agreen&name");
}

void MainWindow::SearchForCardDetails()
{
    QString cardName = ui->resultList->currentItem()->text();
    apiConnector->GetReply(REQUEST_CARD_DETAIL, cardName);
}

void MainWindow::SetCardsList(QStringList cardList)
{
    ui->resultList->addItems(cardList);
}

void MainWindow::SetCardsDetails(Card card)
{
    //TODO obsługa szczegółow karty
}
