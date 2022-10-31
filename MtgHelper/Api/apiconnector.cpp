#include "apiconnector.h"

APIConnector::APIConnector(QObject* parent): QObject(parent), cardList()
{
    data.clear();
    status = STATUS_NONE;
    currentRequestType = REQUEST_CARD_LIST;

    connect(&networkManager, &QNetworkAccessManager::sslErrors, this, &APIConnector::SSLError);
}

void APIConnector::SearchCardList(QString query)
{
    QUrl url = link[REQUEST_CARD_LIST].arg(query);
    QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished,      this, &APIConnector::FinishedReadCardList);
    connect(reply, &QNetworkReply::readyRead,     this, &APIConnector::ReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &APIConnector::ReplyError);
}

void APIConnector::SearchCardDetails(QString query)
{
    status = STATUS_NONE;
    currentRequestType = REQUEST_CARD_DETAIL;

    QUrl url = link[currentRequestType].arg(query);
    QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished,      this, &APIConnector::FinishedReadCardInfo);
    connect(reply, &QNetworkReply::readyRead,     this, &APIConnector::ReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &APIConnector::ReplyError);
}

void APIConnector::SearchCardFrontImage(QString query)
{
    status = STATUS_NONE;
    currentRequestType = REQUEST_CARD_IMAGE;

    QUrl url = link[REQUEST_CARD_IMAGE].arg(query);
    QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished,      this, &APIConnector::FinishedReadCardFrontImage);
    connect(reply, &QNetworkReply::readyRead,     this, &APIConnector::ReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &APIConnector::ReplyError);
}

void APIConnector::SearchCardBackImage(QString query)
{
    status = STATUS_NONE;
    currentRequestType = REQUEST_CARD_IMAGE;

    QUrl url = link[REQUEST_CARD_IMAGE].arg(query);
    QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished,      this, &APIConnector::FinishedReadCardBackImage);
    connect(reply, &QNetworkReply::readyRead,     this, &APIConnector::ReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &APIConnector::ReplyError);
}

void APIConnector::FinishedReadCardList()
{
    if(status == STATUS_OK)
    {
        QStringList cardFound = JsonParser::GetCardList(&data);
        cardList += cardFound;
        emit CardListRead(cardFound);
    }

    if(JsonParser::MoreThanSinglePage(&data) && cardList.count() < MAX_CARD_LIST)
    {
        SearchCardList(JsonParser::GetNextPageURL(&data));
    }
    else
        cardList.clear();

    data.clear();
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();
}


void APIConnector::FinishedReadCardInfo()
{
    if(status == STATUS_OK)
    {
        Card* cardDetails = JsonParser::GetCard(&data);
        emit CardDetailsRead(cardDetails);
    }

    data.clear();
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();
}

void APIConnector::FinishedReadCardFrontImage()
{
    if(status == STATUS_OK)
    {
        QPixmap image = JsonParser::GetCardImage(&data);
        emit CardImageFrontRead(image);
    }

    data.clear();
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();
}

void APIConnector::FinishedReadCardBackImage()
{
    if(status == STATUS_OK)
    {
        QPixmap image = JsonParser::GetCardImage(&data);
        emit CardImageBackRead(image);
    }

    data.clear();
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();
}

void APIConnector::ReadyRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    data.append(reply->readAll());
    status = STATUS_OK;
}

void APIConnector::SSLError(QNetworkReply* reply, const QList<QSslError> &errors)
{
    QString errorString;
    for (const QSslError &error : errors)
    {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }

    reply->ignoreSslErrors();
    // TODO logi
}

void APIConnector::ReplyError(QNetworkReply::NetworkError errorCode)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QNetworkReply::NetworkError error = reply->error();

    const QString &errorString = reply->errorString();
    if (error != QNetworkReply::NoError)
    {
        status = STATUS_ERROR;
        // TODO logi
    }
}
