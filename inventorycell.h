#ifndef INVENTORYCELL_H
#define INVENTORYCELL_H
#include <QTableWidgetItem>
#include "item.h"

class InventoryCell : public QTableWidgetItem {
public:
    InventoryCell(Item* item = NULL, int itemCount = 0);
    ~InventoryCell();
    QString getType();
    int getCount();
    QString getPicture();
    bool isEmpty();
    void clear();
    void setItem(Item* item);
    bool adding(InventoryCell *cell);
    bool increase(int value = 1);
    bool decrease(int value = 1);
    void repaint();

private:
    Item* item;
    int itemCount;
};

#endif // INVENTORYCELL_H
