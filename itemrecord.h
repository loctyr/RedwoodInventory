#ifndef ITEMRECORD_H
#define ITEMRECORD_H

#include <QString>

/**
 * @brief The ItemRecord class - data transfer object to receive inventory item
 */
struct ItemRecord {
    int id = 0; //! index in inventory
    QString type = ""; //! type of item
    int count = 0; //! count of items
    ItemRecord(const int id_, const QString& type_, const int count_);
};

#endif //ITEMRECORD_H
