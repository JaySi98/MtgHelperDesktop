#ifndef DATABASECONNECTOR
#define DATABASECONNECTOR

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPluginLoader>
#include <QSqlDriver>
#include <QVariant>

class DatabaseConnector : public QObject
{
     Q_OBJECT
public:
    explicit DatabaseConnector(QObject *parent = nullptr);

    void connect_database();
    void disconnect_database();

signals:

private:
    QSqlDatabase database;

};

#endif // DATABASECONNECTOR
