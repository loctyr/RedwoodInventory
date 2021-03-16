#include "item.h"
#include "dbadapter.h"

Item::Item(QString type_, QWidget *parent) : QLabel(parent), type(type_) {
    setPixmap(QPixmap(getImagePath()));
}

QString Item::getType() {
    return this->type;
}

QString Item::getImagePath() {
    DBAdapter* adapter = DBAdapter::getInstance();
    return adapter->getImagePath(getType());
}

QString Item::getSoundPath() {
    DBAdapter* adapter = DBAdapter::getInstance();
    return adapter->getSoundPath(getType());
}

void Item::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("text/csv"))
        event->accept();
    else
        event->ignore();
}

void Item::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void Item::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("text/csv")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void Item::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("text/csv")) {
        event->ignore();
    }
}

void Item::mousePressEvent(QMouseEvent *event) {
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    int count = 1;
    dataStream << QString("source") << count << this->getType();

    QMimeData *mimeData = new QMimeData();
    mimeData->setData("text/csv", itemData);

    QDrag *drag = new QDrag(this);
    drag->setPixmap(QPixmap(this->getImagePath()));
    drag->setHotSpot(event->pos());
    drag->setMimeData(mimeData);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction))
    {

    }
}
