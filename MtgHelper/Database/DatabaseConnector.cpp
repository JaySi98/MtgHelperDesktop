#include "DatabaseConnector.h"

DatabaseConnector::DatabaseConnector(QObject *parent)
    : QObject{parent}
{}

void DatabaseConnector::connect_database()
{
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("mtgAdmin");
    database.setPassword("mtgAdmin#123");

    if(!database.open())
    {
        qInfo() << "Failed to connect: " << database.lastError().text();
    }
    else
    {
        qInfo() << "Connected to database";
    }
}

void DatabaseConnector::disconnect_database()
{
    database.close();
    qInfo() << "Disconnected from database";

}
