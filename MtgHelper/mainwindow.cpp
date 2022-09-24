#include <QSharedPointer>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

static bool cardInList(QString cardName, const QList<QSharedPointer<Card>>& cardList);
static QSharedPointer<Card> getCardFromListByName(QString cardName, const QList<QSharedPointer<Card>>& cardList);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , apiConnector(new APIConnector())
    , cardsRememberd(QList<QSharedPointer<Card>>())
    , currentCard(nullptr)
    , p_card_details_view(nullptr)
{
    ui->setupUi(this);

    connect(ui->buttonSearch,   &QToolButton::pressed,          this, &MainWindow::SearchButtonPressed);
    connect(ui->resultList,     &QListWidget::itemPressed,      this, &MainWindow::ListItemPressed);

    connect(apiConnector,       &APIConnector::CardListRead,    this, &MainWindow::SetCardsList);
    connect(apiConnector,       &APIConnector::CardDetailsRead, this, &MainWindow::addCardToRemembered);
    connect(apiConnector,       &APIConnector::CardImageRead,   this, &MainWindow::SetCardImage);
}

MainWindow::~MainWindow()
{
    delete apiConnector;
    delete ui;
}

// slots ===========================================
void MainWindow::SearchButtonPressed()
{
    ui->resultList->clear();
    cardsRememberd.clear();
    currentCard = nullptr;
    qDebug() << "SearchButtonPressed: cardsRememberd.count = " << cardsRememberd.count();

    QString query = ui->searchLine->text();
    apiConnector->SearchCardList(query);
}

void MainWindow::ListItemPressed()
{
    QString cardName = ui->resultList->currentItem()->text();

    if(cardInList(cardName, this->cardsRememberd))
    {
        currentCard = getCardFromListByName(cardName, this->cardsRememberd);
        SetCardsDetails(currentCard.get());
    }
    else
    {
        apiConnector->SearchCardDetails(cardName);
    }
}

void MainWindow::addCardToRemembered(Card *card)
{
    QSharedPointer<Card> pCard = QSharedPointer<Card>(card);
    cardsRememberd.append(pCard);
    currentCard = pCard;
    qDebug() << "addCardToRemembered: cardsRememberd.count = " << cardsRememberd.count();

    apiConnector->SearchCardImage(currentCard.get()->details[SIDE_FACE].imageUrl);
}

void MainWindow::SetCardsList(QStringList cardList)
{
    ui->resultList->addItems(cardList);
}

void MainWindow::SetCardImage(QPixmap image)
{
    currentCard.get()->details[SIDE_FACE].image = image;
    SetCardsDetails(currentCard.get());
}

void MainWindow::SetCardsDetails(Card* card)
{
    p_card_details_view.clear();

    CardDetailsView cdv(this);
    p_card_details_view = QSharedPointer<QWidget>(cdv.GetCardDetailsView(*card));
    ui->scrollArea->setWidget(p_card_details_view.get());
}

// statics ===========================================
static bool cardInList(QString cardName, const QList<QSharedPointer<Card>>& cardList)
{
    foreach(QSharedPointer<Card> card, cardList)
    {
        if(card.get()->details[0].name.compare(cardName) == 0)
            return true;
    }

    return false;
}

static QSharedPointer<Card> getCardFromListByName(QString cardName, const QList<QSharedPointer<Card>>& cardList)
{
    foreach(QSharedPointer<Card> card, cardList)
    {
        if(card.get()->details[0].name.compare(cardName) == 0)
            return card;
    }

    throw std::out_of_range("no card in list");
}
