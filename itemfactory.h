#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QString>
class Item;
class QWidget;

class ItemFactory {
    ItemFactory() = delete;
public:
    static Item* createItem(QString name, QWidget *parent);
};

#endif // ITEMFACTORY_H
