#include "itemfactory.h"
#include "appleitem.h"

Item *ItemFactory::createItem(QString type) {
    if (0 == type.compare("Apple")) {
        return new AppleItem();
    }
    return nullptr;
}
