#ifndef DBADAPTER_H
#define DBADAPTER_H

#include <QtSql/qtsqlglobal.h>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

#include "itemrecord.h"

/**
 * @brief The DBAdapter class - the class for working with database (SQLite DB)
 */
class DBAdapter
{
protected:
    DBAdapter();
    static DBAdapter* singleton;

    bool isOpen();
    void init();
    void close();
public:
    DBAdapter(DBAdapter &other) = delete;
    void operator=(const DBAdapter &) = delete;

    static DBAdapter *getInstance();
    ~DBAdapter();

    QString getSoundPath(QString type);
    QString getImagePath(QString type);
    QStringList getAllItemTypes();
    QList<ItemRecord> getInventory();
    bool insertOrUpdateInventory(QString type, int count, int id);

private:
    QSqlDatabase sqliteDataBase;
};

#endif // DBADAPTER_H
