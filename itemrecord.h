#ifndef ITEMRECORD_H
#define ITEMRECORD_H

#include <QString>

struct ItemRecord {
    int id = 0;
    QString type = "";
    int count = 0;
    ItemRecord(const int id_, const QString& type_, const int count_);
};

#endif //ITEMRECORD_H
