#ifndef APICONNECTOR_H
#define APICONNECTOR_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QAuthenticator>
#include <QNetworkProxy>

#include "jsonparser.h"
#include "card.h"

#define URL_TYPES_COUNT 2

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
    void CardDetailsRead(Card card);

public slots:
    void GetReply(requestType type, QString query);

private slots:
    void ReadyRead();
    void Finished(QNetworkReply* reply);
    void SSLError(QNetworkReply* reply, const QList<QSslError> &errors);
    void ReplyError(QNetworkReply::NetworkError errorCode);

private:

    typedef enum
    {
        STATUS_NONE        = 0,
        STATUS_OK          = 1, // success
        STATUS_ERROR       = 2, // failed to download Json
        STATUS_JSON_ERROR  = 4, // failed to parse Json
    }requestStatus;

    // https://api.scryfall.com/cards/search?q=Ambitious%20Farmhand%20//%20Seasoned%20Cathar
    // https://api.scryfall.com/cards/named?exact=%1
    // https://api.scryfall.com/cards/named?fuzzy=%1
    // https://api.scryfall.com/cards/%1
    const QString link[URL_TYPES_COUNT]= {"https://api.scryfall.com/cards/search?q=%1",
                                          "https://api.scryfall.com/cards/named?exact=%1"};

    QNetworkAccessManager networkManager;
    QByteArray data;
    requestStatus status;
    requestType currentRequestType;
};

#endif // APICONNECTOR_H


/*!
 * linki:
 *
 *      - https://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
 *      - https://en.wikipedia.org/wiki/Percent-encoding
 *      - https://dev.to/truepadawan/qt-c-working-with-rest-api-35fe
 *      - https://docs.magicthegathering.io/
 *      - https://scryfall.com/docs/api
 *      - https://api.cardmarket.com/ws/documentation
 *      - https://docs.tcgplayer.com/docs
 * TODO:
 *      - wyświetlanie szczegółów karty
 *
 *      - ogarnąc składnie scryfall
 *      - klasa do tworzenia query
 *      - przejście na mobilne i QML
 *      - lista z ikonami typów
 *      - podpęcie bazy
 *      - zapis kart
 *
 * DRUGIE API:
 *  // https://api.magicthegathering.io/v1/cards/?name=nissa&cmc=5
 *  // https://api.magicthegathering.io/v1/cards/?name=avacyn
 *  const QString urlMTG        = "https://api.magicthegathering.io/v1/cards/%1";
 */
