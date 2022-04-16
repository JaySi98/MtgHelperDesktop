#include "apiconnector.h"

APIConnector::APIConnector(QObject* parent): QObject(parent)
{
    data.clear();
    status = STATUS_NONE;
    currentRequestType = REQUEST_CARD_LIST;

    connect(&networkManager, &QNetworkAccessManager::finished,  this, &APIConnector::Finished);
    connect(&networkManager, &QNetworkAccessManager::sslErrors, this, &APIConnector::SSLError);
}

/*!
 * @brief
 */
void APIConnector::GetReply(requestType type, QString query)
{
    status = STATUS_NONE;
    currentRequestType = type;

    QUrl url = link[type].arg(query);
    QNetworkReply* reply = networkManager.get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::readyRead,     this, &APIConnector::ReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &APIConnector::ReplyError);
}

/*!
 * @brief
 */
void APIConnector::ReadyRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    data.append(reply->readAll());
    status = STATUS_OK;
}

/*!
 * @brief
 */
void APIConnector::Finished(QNetworkReply* reply)
{    
    if(status == STATUS_OK)
    {
        // TODO wyjątki
        switch (currentRequestType)
        {
            case REQUEST_CARD_LIST:
            {
                QStringList cardList = JsonParser::GetCardList(&data);
                emit CardListRead(cardList);
                break;
            }

            case REQUEST_CARD_DETAIL:
            {
                Card cardDetails = JsonParser::GetCard(&data);
                emit CardDetailsRead(cardDetails);
                break;
            }

            case REQUEST_CARD_IMAGE:
            {
                QPixmap image = JsonParser::GetCardImage(&data);
                emit CardImageRead(image);
                break;
            }
        }
    }

    data.clear();
}

/*!
 * @brief
 */
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

/*!
 * @brief
 */
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
