#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);
    reply = nullptr;
    dataBuffer = new QByteArray();

    connect(ui->buttonSearch,&QToolButton::pressed, this, &MainWindow::Search);
}

MainWindow::~MainWindow()
{
    delete networkManager;
    delete dataBuffer;

    delete ui;
}

void MainWindow::Search()
{
    QNetworkRequest req{QUrl(this->url)};
    reply = networkManager->get(req);
    connect(reply, &QNetworkReply::readyRead, this, &MainWindow::ReadData);
    connect(reply, &QNetworkReply::finished,  this, &MainWindow::FinishReading);
}

void MainWindow::ReadData()
{
    dataBuffer->append(reply->readAll());
}

void MainWindow::FinishReading()
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error : " << reply->errorString();
        //QMessageBox::warning(this,"Error",QString("Request[Error] : %1").arg(netReply->errorString()));
    }
    else
    {

        //CONVERT THE DATA FROM A JSON DOC TO A JSON OBJECT
        QJsonObject userJsonInfo = QJsonDocument::fromJson(*dataBuffer).object();
        QJsonObject card = userJsonInfo.find("card")->toObject();

        //SET TEXT
//        QString name = card.value("name").toString();
//        QString type = card.value("type").toString();
//        QString text = card.value("text").toString();

//        ui->labelName->setText(name);
//        ui->labelType->setText(type);
//        ui->labelText->setText(text);

        //SET PICTURE
//        auto picLink = userJsonInfo.value("avatar_url").toString();
//        QNetworkRequest link{QUrl(picLink)};
//        reply = netManager->get(link);
//        connect(reply,&QNetworkReply::finished,this,&MainWindow::setUserImage);
        dataBuffer->clear();
    }
}
