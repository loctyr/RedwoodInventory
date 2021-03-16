#include "dbadapter.h"
#include <QDebug>


/**
 *  * Description of tables:
 * ****************
 *
 * 1) Table of item types (itemTable)
 *
 * 1. VARCHAR(255) type     - Item type;
 * 2. VARCHAR(255) picture  - Path to image resource;
 * 3. VARCHAR(255) sound    - Path to sound resource;
 *
 * 2) Inventory table (inventory)
 *
 * 1. integer      id       - index in inventory;
 * 2. integer      count    - count of items;
 * 3. VARCHAR(255) type     - Item type;
 *
**/
DBAdapter* DBAdapter::singleton= nullptr;;

DBAdapter::DBAdapter() {
    sqliteDataBase = QSqlDatabase::addDatabase("QSQLITE");
    sqliteDataBase.setDatabaseName("inventory.sqlite");
    if (!sqliteDataBase.open()) {
        qDebug() << sqliteDataBase.lastError().text();
    }
    init();
}

DBAdapter *DBAdapter::getInstance() {
    if(nullptr == singleton){
        singleton = new DBAdapter();
    }
    return singleton;
}

DBAdapter::~DBAdapter() {
    if (isOpen()) {
        sqliteDataBase.close();
        QSqlDatabase::removeDatabase("QSQLITE");
    }
}

bool DBAdapter::isOpen() {
    return sqliteDataBase.isOpen();
}

void DBAdapter::init() {
    QSqlQuery query = QSqlQuery(sqliteDataBase);
    query.exec("CREATE TABLE IF NOT EXISTS item (type VARCHAR(255) NOT NULL, picture VARCHAR(255), sound VARCHAR(255), PRIMARY KEY(type))");
    query.exec("CREATE TABLE IF NOT EXISTS inventory (id INTEGER PRIMARY KEY, count INTEGER, type VARCHAR(255), FOREIGN KEY(type) REFERENCES item(type))");
    query.exec("INSERT INTO item (picture, type, sound) VALUES (\":/images/apple.jpg\", \"Apple\", \"qrc:/sound/apple.mp3\");");
}

QString DBAdapter::getSoundPath(QString type) {
    DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase);
    query.exec("SELECT sound from item WHERE type = \'" + type + "\';");
    QString soundPath;
    if (query.first()) {
        soundPath = query.value("sound").toString();
    }
    return soundPath;
}

QString DBAdapter::getImagePath(QString type) {
    DBAdapter* adapter = DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase);
    query.exec("SELECT picture FROM item WHERE type = \'" + type + "\';");
    QString imagePath;
    if (query.first()) {
        imagePath = query.value("picture").toString();
    }
    return imagePath;
}

QStringList DBAdapter::getAllItemTypes() {
    QStringList list;

    DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase);
    query.exec("SELECT type from item;");
    while(query.next()) {
        list.append(query.value("type").toString());
    }
    return list;
}

QList<ItemRecord> DBAdapter::getInventory() {
    QList<ItemRecord> result;
    DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase) ;
    if (!query.exec("SELECT id, type, count FROM inventory;")) {
        qDebug() << query.lastError().text();
        return result;
    }
    while (query.next()) {
        result.push_back({query.value("id").toInt(),query.value("type").toString(),query.value("count").toInt()});
    }

    return result;
}

bool DBAdapter::insertOrUpdateInventory(QString type, int count, int id) {
    DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase) ;

    QString queryText = "INSERT or REPLACE INTO inventory (id, type, count) VALUES (" + QString::number(id) + ", \'" + type + "\', " + QString::number(count) + ");";
    if (!query.exec(queryText)) {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}
