#include "itemlabel.h"
#include "dbadapter.h"

ItemLabel::ItemLabel(Item* item_, QWidget *parent) : QLabel(parent), item(item_) {
    setAttribute(Qt::WA_DeleteOnClose);
    if (!item.isNull()) {
        setPixmap(item->getImagePath());
    }
}


void ItemLabel::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("text/csv"))
        event->accept();
    else
        event->ignore();
}

void ItemLabel::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void ItemLabel::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("text/csv")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void ItemLabel::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("text/csv")) {
        event->ignore();
    }
}

void ItemLabel::mousePressEvent(QMouseEvent *event) {
    if (item.isNull()) return;

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    int count = 1;
    dataStream << QString("source") << count << item->getType();

    QMimeData *mimeData = new QMimeData();
    mimeData->setData("text/csv", itemData);

    QDrag drag(this);
    drag.setPixmap(QPixmap(item->getImagePath()));
    drag.setHotSpot(event->pos());
    drag.setMimeData(mimeData);

    drag.exec(Qt::MoveAction);
}
