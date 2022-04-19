#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    apiConnector = new APIConnector();
    cardDetailsView = new CardDetailsView(this);

    connect(ui->buttonSearch,   &QToolButton::pressed,          this, &MainWindow::SearchForCards);
    connect(ui->resultList,     &QListWidget::itemPressed,      this, &MainWindow::SearchForCardDetails);
    connect(apiConnector,       &APIConnector::CardListRead,    this, &MainWindow::SetCardsList);
    connect(apiConnector,       &APIConnector::CardDetailsRead, this, &MainWindow::SetCardsDetails);
    connect(apiConnector,       &APIConnector::CardImageRead,   this, &MainWindow::SetCardImage);
}

MainWindow::~MainWindow()
{
    delete apiConnector;
    delete cardDetailsView;
    delete ui;
}

void MainWindow::SearchForCards()
{
    //TODO budowanie query
    ui->resultList->clear();

    QString query = ui->searchLine->text();
    apiConnector->GetReply(REQUEST_CARD_LIST, query);
}

void MainWindow::SearchForCardDetails()
{
   //TODO poprawić wybieranie elementu
    QString cardName = ui->resultList->currentItem()->text();
    apiConnector->GetReply(REQUEST_CARD_DETAIL, cardName);
}

void MainWindow::SetCardsList(QStringList cardList)
{
    //TODO lista z znaczkami typow
    ui->resultList->addItems(cardList);
}

void MainWindow::SetCardsDetails(Card card)
{
    //TODO dodawanie widoku szczegółów karty
    QWidget* cardDetails = cardDetailsView->GetCardDetailsView(card);
    ui->scrollArea->setWidget(cardDetails);
}

void MainWindow::SetCardImage(QPixmap image)
{
    // TODO dodawanie obrazku
    QGraphicsScene* cardImage = cardDetailsView->GetCardImage(image);
    ui->graphicsView->setScene(cardImage);
    ui->graphicsView->show();
}
