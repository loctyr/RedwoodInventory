#include "inventorycell.h"

InventoryCell::InventoryCell(Item *item_, int count_) {
    item = item_;
    itemCount = count_;
    this->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
}

InventoryCell::~InventoryCell() {
    delete item;
}

QString InventoryCell::getType() {
    if (!this->isEmpty()) {
        return this->item->getType();
    }
    return QString();
}

int InventoryCell::getCount() {
    return this->itemCount;
}

QString InventoryCell::getPicture() {
    if (item) {
        return item->getImagePath();
    }
    return QString("");
}

bool InventoryCell::isEmpty() {
    return (this->itemCount == 0 || this->item == NULL);
}

bool InventoryCell::increase(int value) {
    if (!this->isEmpty()) {
        itemCount += value;
        return true;
    }
    return false;
}

bool InventoryCell::decrease(int value) {
    if (!isEmpty()) {
        itemCount -= value;
        item->removeAction();
        if (this->itemCount <= 0) {
            this->clear();
        }
        repaint();
        return true;
    }
    return false;
}

void InventoryCell::clear() {
    itemCount = 0;
    delete this->item;
    item = nullptr;
}

void InventoryCell::setItem(Item *item) {
    this->item = item;
}

void InventoryCell::repaint() {
    if (item != nullptr)     {
        QImage *img = new QImage();
        if (img->load(this->item->getImagePath())) {
            this->setData(Qt::BackgroundColorRole, QPixmap::fromImage(*img));
        }
        if (this->itemCount > 0) {
            setText(QString::number(this->itemCount));
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
