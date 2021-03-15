#include "dbadapter.h"

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
    if (this->isOpen()) {
        this->close();
    }
}

void DBAdapter::close() {
    if (this->isOpen()) {
        this->sqliteDataBase.close();
        QSqlDatabase::removeDatabase("QSQLITE");
    }
}

bool DBAdapter::isOpen() {
    return this->sqliteDataBase.isOpen();
}

void DBAdapter::init() {
    QSqlQuery query = QSqlQuery(sqliteDataBase);
    query.exec("CREATE TABLE IF NOT EXISTS itemTable (picture VARCHAR(255), type VARCHAR(255) NOT NULL, sound VARCHAR(255), PRIMARY KEY(type))");
    query.exec("CREATE TABLE IF NOT EXISTS inventoryTable (id INTEGER PRIMARY KEY, count INTEGER, type VARCHAR(255), FOREIGN KEY(type) REFERENCES itemTable(type))");
    query.exec("INSERT INTO itemTable (picture, type, sound) VALUES (\":/images/apple.jpg\", \"Apple\", \":/sound/apple.mp3\");");
}

QString DBAdapter::getSoundPath(QString type) {
    DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase);
    query.exec("SELECT sound from itemTable WHERE type = \'" + type + "\';");
    QString soundPath;
    if (query.first()) {
        soundPath = query.value("sound").toString();
    }
    return soundPath;
}

QString DBAdapter::getImagePath(QString type) {
    DBAdapter* adapter = DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase);
    query.exec("SELECT picture FROM itemTable WHERE type = \'" + type + "\';");
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
    query.exec("SELECT type from itemTable;");
    while(query.next()) {
        list.append(query.value("type").toString());
    }
    return list;
}

QList<ItemRecord> DBAdapter::getInventory() {
    QList<ItemRecord> result;
    DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase) ;
    if (query.exec("SELECT id, type, count FROM inventoryTable")) {
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
    if (!query.exec("UPDATE inventoryTable SET type = \'" + type + "\', count = " + QString::number(count) + "\' WHERE id = " + QString::number(id) + ";")) {
        if (!query.exec("INSERT INTO inventoryTable (id, type, count) VALUES (" + QString::number(id) + ", \'" + type + "\', " + QString::number(count) + ");")) {
            return false;
        }
    }
}
