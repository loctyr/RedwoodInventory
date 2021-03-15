#include "inventory.h"
#include "itemfactory.h"
#include "dbadapter.h"

Inventory::Inventory(int rows, int columns, QWidget *parent) : QTableWidget(rows, columns, parent) {
    horizontalSize = rows;
    verticalSize = columns;

    init();
}

Inventory::Inventory(QWidget *parent) : QTableWidget(parent) {
}

Inventory::~Inventory() {
}

void Inventory::setRowCount(int rows) {
    horizontalSize = rows;
    QTableWidget::setRowCount(rows);
    init();
}

void Inventory::setColumnCount(int columns) {
    verticalSize = columns;
    QTableWidget::setColumnCount(columns);
    init();
}

InventoryCell* Inventory::getCell(int x, int y) {
    if ((x >= 0 && x < horizontalSize) && (y >= 0 && y < verticalSize)) {
        return dynamic_cast<InventoryCell*>(takeItem(x,y));
    }
    return nullptr;
}

void Inventory::setCell(InventoryCell *cell, int x, int y) {
    delete takeItem(x,y);
    setItem(y, x, cell);
}

void Inventory::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("text/csv")) {
        event->accept();
    } else {
        event->ignore();
    }
}

void Inventory::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void Inventory::dragMoveEvent(QDragMoveEvent *event) {
    this->repaintAllCells();
    QPoint target = getIndex(event->pos());
    if (target.x() >= 0) {
        getCell(target.x(), target.y())->setBackgroundColor(QColor(100, 100, 255, 100));
    }

    if (event->mimeData()->hasFormat("text/csv")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void Inventory::dropEvent(QDropEvent *event) {
    repaintAllCells();
    if (event->mimeData()->hasFormat("text/csv")) {
        QByteArray pieceData = event->mimeData()->data("text/csv");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QString message;
        dataStream >> message;
        if (message ==  "from inventory") {
            QPoint sourceCell;
            dataStream >> sourceCell;
            QPoint targetCell = this->getIndex(event->pos());
            if (targetCell.x() >= 0) {
                if (!((targetCell.x() == sourceCell.x()) && (targetCell.y() == sourceCell.y()))) {
                    this->getCell(targetCell.x(), targetCell.y())->adding(this->getCell(sourceCell.x(), sourceCell.y()));
                    refreshCell(targetCell.x(), targetCell.y());
                    refreshCell(sourceCell.x(), sourceCell.y());
                }
            }
        } else {
            if (message == "source") {
                int itemCount;
                QString itemType;
                dataStream >> itemCount >> itemType;
                QPoint target = getIndex(event->pos());
                qDebug() << "from source. Count : " << itemCount << ". Type : " << itemType;
                if (target.x() >= 0) {
                    this->getCell(target.x(), target.y())->adding(new InventoryCell(ItemFactory::createItem(itemType, this), itemCount));
                    refreshCell(target.x(), target.y());
                }
            }
        }

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void Inventory::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        QPoint target = getIndex(event->pos());
        if (target.x() >= 0) {
            dataStream << QString("from inventory") << target;
            QMimeData *mimeData = new QMimeData;
            mimeData->setData("text/csv", itemData);

            QDrag *drag = new QDrag(this);
            drag->setPixmap(QPixmap(this->getCell(target.x(), target.y())->getPicture()));
            drag->setHotSpot(QPoint(event->pos().x() - target.x()*100, event->pos().y() - target.y()*100));
            drag->setMimeData(mimeData);

            if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
            }
        }
    } else {
        QPoint target = this->getIndex(event->pos());
        if (target.x() >= 0) {
            getCell(target.x(), target.y())->decrease();
            refreshCell(target.x(), target.y());
        }
    }
}

void Inventory::init() {
    for (int i = 0; i < horizontalSize; i++) {
        for (int j = 0; j < verticalSize; j++) {
            if (nullptr != getCell(j, i)) {
                delete getCell(j, i);
            }
            InventoryCell* cell = new InventoryCell(nullptr, 0);
            setCell(cell, j, i);
        }
    }

    horizontalHeader()->setDefaultSectionSize(100);
    verticalHeader()->setDefaultSectionSize(100);

    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    this->loadFromBD();
}

void Inventory::saveToBD() {
    DBAdapter *adapter = DBAdapter::getInstance();
    for (int j = 0; j < this->verticalSize; j++) {
        for (int i = 0; i < this->horizontalSize; i++) {
            adapter->insertOrUpdateInventory(getCell(i, j)->getType(),this->getCell(i, j)->getCount(),(j*this->horizontalSize) + i);
        }
    }
}

void Inventory::loadFromBD() {
    DBAdapter *adapter = DBAdapter::getInstance();
    QList<ItemRecord> record_list = adapter->getInventory();
    for(auto it = record_list.begin(); it != record_list.end(); ++it) {
      setCell(new InventoryCell(ItemFactory::createItem(it->type, this), it->count), (it->id) % this->horizontalSize, (it->id)/this->horizontalSize);
    }
    repaintAllCells();
}

void Inventory::refreshCell(int x, int y) {
    DBAdapter *adapter = DBAdapter::getInstance();
    adapter->insertOrUpdateInventory(getCell(x, y)->getType(),this->getCell(x, y)->getCount(),(y*this->horizontalSize) + x);
}

QPoint Inventory::getIndex(QPoint pos) {
    if ((pos.x() < this->horizontalSize * 100 + DELTA_X) && (pos.y() < verticalSize * 100 + DELTA_Y))
    {
        return QPoint((pos.x() - DELTA_X)/100, (pos.y() - DELTA_Y)/100);
    }
    return QPoint(-1, -1);
}

void Inventory::repaintAllCells() {
    for (int i = 0; i < this->verticalSize; i++) {
        for (int j = 0; j < this->horizontalSize; j++) {
            InventoryCell* cell=nullptr;
            if (nullptr != cell) {
                cell->repaint();
            }
        }
    }
}

void Inventory::newGame() {
    for (int i = 0; i < verticalSize; i++) {
        for (int j = 0; j < horizontalSize; j++)
        {
            InventoryCell* cell = new InventoryCell(NULL, 0);
            this->setCell(cell, j, i);
        }
    }
    this->saveToBD();
}

