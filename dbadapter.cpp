#include "dbadapter.h"

DBAdapter* DBAdapter::singleton= nullptr;;

DBAdapter::DBAdapter() {
    sqliteDataBase = QSqlDatabase::addDatabase("QSQLITE");
    sqliteDataBase.setDatabaseName("mydatabase.sqlite");
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

QSqlQuery* DBAdapter::exec(QString sqlRequest) {
    QSqlQuery* currentQuerry = new QSqlQuery();
    currentQuerry->exec(sqlRequest);
    return currentQuerry;
}

void DBAdapter::init() {
    QSqlQuery query = QSqlQuery(sqliteDataBase);
    query.exec("CREATE TABLE IF NOT EXISTS itemTable (picture VARCHAR(255), type VARCHAR(255) NOT NULL, sound VARCHAR(255), PRIMARY KEY(type))");
    query.exec("CREATE TABLE IF NOT EXISTS inventoryTable (id INTEGER PRIMARY KEY, count INTEGER, type VARCHAR(255), FOREIGN KEY(type) REFERENCES itemTable(type))");
    query.exec("INSERT INTO itemTable (picture, type, sound) VALUES (\":/images/apple.jpg\", \"Apple\", \":/sound/apple.mp3\");");
}

QSqlQuery* DBAdapter::getConnection() {
    return new QSqlQuery();
}

QString DBAdapter::getSoundPath(QString type) {
    DBAdapter* adapter = DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase);
    query.exec("SELECT sound from itemTable WHERE type = \'" + type + "\';");
    QString soundPath;
    if (query.first()) {
        soundPath = query.value(0).toString();
    }
    return soundPath;
}

QString DBAdapter::getImagePath(QString type) {
    DBAdapter* adapter = DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase);
    query.exec("SELECT picture from itemTable WHERE type = \'" + type + "\';");
    QString imagePath;
    if (query.first()) {
        imagePath = query.value(0).toString();
    }
    return imagePath;
}

QStringList DBAdapter::getAllItemTypes() {
    QStringList list;

    DBAdapter* adapter = DBAdapter::getInstance();
    QSqlQuery query(sqliteDataBase);
    query.exec("SELECT type from itemTable;");
    while(query.next()) {
        list.append(query.value(0).toString());
    }
    return list;
}
