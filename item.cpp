#include "item.h"
#include "dbadapter.h"

Item::Item(QString type_) : type(type_) {
    DBAdapter* adapter = DBAdapter::getInstance();
    imagePath = adapter->getImagePath(getType());
    soundPath = adapter->getSoundPath(getType());
}

QString Item::getType() {
    return type;
}

QString Item::getImagePath() {
    return imagePath;
}

QString Item::getSoundPath() {
    return soundPath;
}
