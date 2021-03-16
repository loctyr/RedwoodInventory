#include "inventorycell.h"

InventoryCell::InventoryCell(Item *item_, int count_) {
    item = item_;
    itemCount = count_;
    setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
}

InventoryCell::~InventoryCell() {
    delete item;
}

QString InventoryCell::getType() {
    if (!isEmpty()) {
        return item->getType();
    }
    return QString();
}

int InventoryCell::getCount() {
    return itemCount;
}

QString InventoryCell::getImage() {
    if (item) {
        return item->getImagePath();
    }
    return QString("");
}

bool InventoryCell::isEmpty() {
    return (itemCount == 0 || item == NULL);
}

bool InventoryCell::increase(int value) {
    if (!isEmpty()) {
        itemCount += value;
        return true;
    }
    return false;
}

bool InventoryCell::decrease(int value) {
    if (!isEmpty()) {
        itemCount -= value;
        item->removeAction();
        if (itemCount <= 0) {
            clear();
        }
        repaint();
        return true;
    }
    return false;
}

void InventoryCell::clear() {
    itemCount = 0;
    delete item;
    item = nullptr;
}

void InventoryCell::setItem(Item *item_) {
    item = item_;
}

void InventoryCell::repaint() {
    if (item != nullptr)     {
        QImage *img = new QImage();
        if (img->load(item->getImagePath())) {
            setData(Qt::BackgroundColorRole, QPixmap::fromImage(*img));
        }
        if (itemCount > 0) {
            setText(QString::number(itemCount));
        } else {
            setText("");
        }
    } else {
        setText("");
        setBackgroundColor(QColor(255, 255, 255, 0));
    }
}

bool InventoryCell::adding(InventoryCell *cell) {
    if (this->getType() == cell->getType()) {
        this->increase(cell->getCount());
        cell->itemCount = 0;
        delete cell->item;
        cell->item = nullptr;
        this->repaint();
        cell->repaint();
        return true;
    } else {
        if (item == nullptr) {
            setItem(cell->item);
            itemCount = cell->getCount();
            cell->itemCount = 0;
            cell->item = NULL;
            cell->repaint();
            repaint();
            return true;
        }
    }
    return false;
}
