#ifndef APICONNECTOR_H
#define APICONNECTOR_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QAuthenticator>
#include <QNetworkProxy>
#include <QPixmap>

#include "jsonparser.h"
#include "card.h"

#define URL_TYPES_COUNT 3
#define MAX_CARD_LIST   348

typedef enum
{
    REQUEST_CARD_LIST   = 0,
    REQUEST_CARD_DETAIL = 1,
    REQUEST_CARD_IMAGE  = 2,
}requestType;


class APIConnector: public QObject
{
    Q_OBJECT

public:
    explicit APIConnector(QObject* parent = nullptr);

signals:
    void CardListRead(QStringList);
    void CardDetailsRead(Card* card);
    void CardImageRead(QPixmap image);

public slots:
    void SearchCardList(QString query);
    void SearchCardDetails(QString query);
    void SearchCardImage(QString query);


private slots:
    void ReadyRead();
    void SSLError(QNetworkReply* reply, const QList<QSslError> &errors);
    void ReplyError(QNetworkReply::NetworkError errorCode);
    void FinishedReadCardList();
    void FinishedReadCardInfo();
    void FinishedReadCardImage();

private:

    typedef enum
    {
        STATUS_NONE        = 0,
        STATUS_OK          = 1, // success
        STATUS_ERROR       = 2, // failed to download Json
        STATUS_JSON_ERROR  = 4, // failed to parse Json
    }requestStatus;

    const QString link[URL_TYPES_COUNT]=
    {
        "https://api.scryfall.com/cards/search?q=%1",
        "https://api.scryfall.com/cards/named?exact=%1",
        "%1"
    };

    QNetworkAccessManager networkManager;
    QByteArray data;
    requestStatus status;
    requestType currentRequestType;
    QStringList cardList;
};

#endif // APICONNECTOR_H


/*!
 * linki:
 *      - https://api.scryfall.com/cards/search?q=Ambitious%20Farmhand%20//%20Seasoned%20Cathar
 *      - https://api.scryfall.com/cards/named?exact=%1
 *      - https://api.scryfall.com/cards/named?fuzzy=%1
 *      - https://api.scryfall.com/cards/%1

 *      - https://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
 *      - https://en.wikipedia.org/wiki/Percent-encoding
 *      - https://dev.to/truepadawan/qt-c-working-with-rest-api-35fe
 *      - https://docs.magicthegathering.io/
 *      - https://scryfall.com/docs/api
 *      - https://api.cardmarket.com/ws/documentation
 *      - https://docs.tcgplayer.com/docs
 * DRUGIE API:
 *  // https://api.magicthegathering.io/v1/cards/?name=nissa&cmc=5
 *  // https://api.magicthegathering.io/v1/cards/?name=avacyn
 *  const QString urlMTG        = "https://api.magicthegathering.io/v1/cards/%1";
 */
