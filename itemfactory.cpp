#include "itemfactory.h"
#include "appleitem.h"

Item *ItemFactory::createItem(QString type, QWidget* parent = nullptr) {
    if (0 == type.compare("Apple")) {
        return new AppleItem(parent);
    }
    return nullptr;
}
