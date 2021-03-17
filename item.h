#ifndef ITEM_H
#define ITEM_H

#include <QString>
/**
 * @brief The Item class - class of any item of inventory
 */
class Item {
public:
    /**
     * @brief Item - create object
     * @param type_ - type of item
     */
    explicit Item(QString type_);

    /**
     * @brief getType - method for getting type of inventory object
     * @return - type of inventory object
     */
    QString getType();

    /**
     * @brief getImagePath - virtual method for getting path of image of this inventory object
     * @return - the path of picture file
     */
    virtual QString getImagePath();

    /**
     * @brief getSoundPath - virtual method for getting path of sound of this inventory object
     * @return - the path of sound file
     */
    virtual QString getSoundPath();

    /**
     * @brief removeAction - virtual method, that performed action of using item (playing sound)
     */
    virtual void removeAction() = 0;

protected:
    QString type; //! item type
    QString imagePath;//! path of picture file
    QString soundPath;//! path of sound file
};

#endif // ITEM_H
