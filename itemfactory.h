#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QString>
class Item;
class QWidget;

/**
 * @brief The ItemFactory class - factory to produce items by type name
 */
class ItemFactory {
    ItemFactory() = delete;
public:
    /**
     * @brief createItem - create item by type name
     * @param name - type of item
     * @param parent - the parent Widget
     * @return - pointer to created item
     */
    static Item* createItem(QString type, QWidget *parent);
};

#endif // ITEMFACTORY_H
