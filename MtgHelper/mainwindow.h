#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // https://api.magicthegathering.io/v1/cards/?name=nissa&cmc=5
    // https://api.magicthegathering.io/v1/cards/?name=avacyn
    const QString url = "https://api.magicthegathering.io/v1/cards/386616";
    QNetworkAccessManager *networkManager;
    QNetworkReply *reply;
    QByteArray *dataBuffer;

    void Search();
    void ReadData();
    void FinishReading();
};
#endif // MAINWINDOW_H



/*!
 * linki:
 *      - https://dev.to/truepadawan/qt-c-working-with-rest-api-35fe
 *      - https://docs.magicthegathering.io/
 *      - https://scryfall.com/docs/api
 *
 * wizja:
 *      - na start wpisywanie nazywy i pobieranie z api
 *      - zapis do bazy
 *      - jeżeli karta jest już w bazie to nie pobieraj
 *      - updatowanie bazy w zależności czy karta jest zapisana?
 */
