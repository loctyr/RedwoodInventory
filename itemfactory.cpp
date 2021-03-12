#include "itemfactory.h"
#include "appleitem.h"

Item *ItemFactory::createItem(QString name, QWidget* parent) {
    if (0 == name.compare("Apple")) {
        return new AppleItem(parent);
    }
    return nullptr;
}
