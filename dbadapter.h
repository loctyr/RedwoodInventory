#ifndef DBADAPTER_H
#define DBADAPTER_H

#include <QtSql/qtsqlglobal.h>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "itemrecord.h"

/**
 * @brief The DBAdapter class - the class for working with database (SQLite DB)
 * implements the singleton pattern
 */
class DBAdapter {
protected:
    /**
     * @brief DBAdapter - create adapter for connecting to database.
     */
    DBAdapter();
    static DBAdapter* singleton;

    /**
     * @brief isOpen - connection with dataBase is opened
     * @return true - if connection is opened
     *             false - if conncetion is closed
     */
    bool isOpen();

    /**
     * @brief init - initializate database with primary data. Create tables and insert item (Apple Item)
     */
    void init();
public:
    DBAdapter(DBAdapter &other) = delete;
    void operator=(const DBAdapter &) = delete;

    /**
      * @brief ~DBAdapter - close connection and destroying this adapter
     */
    ~DBAdapter();

    /**
      * @brief ~getInstance - gives a pointer to a singleton object
      * @return the pointer to a singleton object
     */
    static DBAdapter *getInstance();

    /**
      * @brief getSoundPath - gives the path to the sound file
      * @param type - type of item
      * @return the path to the sound file
     */
    QString getSoundPath(QString type);

    /**
      * @brief getImagePath - gives the path to the image file
      * @param type - type of item
      * @return the path to the image file
     */
    QString getImagePath(QString type);

    /**
      * @brief getAllItemTypes - gives a list of all types of items
      * @return the list of all types of items
     */
    QStringList getAllItemTypes();

    /**
      * @brief getInventory - gives the inventory saved in the database
      * @return the list of all items in the inventory
     */
    QList<ItemRecord> getInventory();

    /**
      * @brief insertOrUpdateInventory - changes inventory cell
     * @return true  - success
     *         false - fail
     */
    bool insertOrUpdateInventory(QString type, int count, int id);

private:
    QSqlDatabase sqliteDataBase; //! the connection to database
};

#endif // DBADAPTER_H
