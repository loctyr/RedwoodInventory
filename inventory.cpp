#include "inventory.h"
#include "itemfactory.h"
#include "dbadapter.h"

#define DELTA_X 0
#define DELTA_Y 0
const int cellHeight = 100;
const int cellWidth  = 100;

Inventory::Inventory(int rows, int columns, QWidget *parent) : QTableWidget(rows, columns, parent) {
    init();
}

Inventory::Inventory(QWidget *parent) : QTableWidget(parent) {
}

Inventory::~Inventory() {
}

void Inventory::setRowCount(int rows) {
    QTableWidget::setRowCount(rows);
    init();
}

void Inventory::setColumnCount(int columns) {
    QTableWidget::setColumnCount(columns);
    init();
}

InventoryCell* Inventory::getCell(int x, int y) {

    if ((x >= 0 && x < rowCount()) && (y >= 0 && y < columnCount())) {
        return dynamic_cast<InventoryCell*>(item(x,y));
    }
    return nullptr;
}

void Inventory::setCell(InventoryCell *cell, int x, int y) {
    delete takeItem(x,y);
    setItem(x, y, cell);
    if (nullptr != cell) {
        cell->setEnabled(isEnabled());
        cell->repaint();
    }
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
    QPoint target = getIndex(event->pos());
    for (int i = 0; i < columnCount(); i++) {
        for (int j = 0; j < rowCount(); j++) {
            if (item(i,j)) {
                item(i,j)->setBackgroundColor(Qt::white);
            }
        }
    }
    repaintAllCells();
    if (target.x() >= 0) {
        getCell(target.x(), target.y())->setBackgroundColor(QColor(100, 100, 255, 100));
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
            QPoint targetCell = getIndex(event->pos());
            if (targetCell.x() >= 0) {
                if (!((targetCell.x() == sourceCell.x()) && (targetCell.y() == sourceCell.y()))) {
                    getCell(targetCell.x(), targetCell.y())->adding(getCell(sourceCell.x(), sourceCell.y()));
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
                if (target.x() >= 0) {
                    InventoryCell* crCell;
                    crCell = getCell(target.x(), target.y());
                    if (nullptr != crCell) {
                        crCell->adding(new InventoryCell(ItemFactory::createItem(itemType, nullptr), itemCount));
                    }
                    refreshCell(target.x(), target.y());
                }
            }
        }

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
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
            drag->setPixmap(QPixmap(getCell(target.x(), target.y())->getImage()));
            drag->setMimeData(mimeData);

            if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
            }
        }
    } else {
        QPoint target = getIndex(event->pos());
        if (target.x() >= 0) {
            getCell(target.x(), target.y())->decrease();
            refreshCell(target.x(), target.y());
        }
    }
}

void Inventory::changeEvent(QEvent *event) {
    QTableWidget::changeEvent(event);
    if (event->type() == QEvent::EnabledChange) {
        for (int i = 0; i < rowCount(); i++) {
            for (int j = 0; j < columnCount(); j++) {
                if (nullptr != getCell(i, j)) {
                    getCell(i, j)->setEnabled(isEnabled());
                    getCell(i, j)->repaint();
                }
            }
        }
    }
}

void Inventory::init() {
    setAcceptDrops(true);
    setDragDropOverwriteMode(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    viewport()->setAcceptDrops(true);

    for (int i = 0; i < rowCount(); i++) {
        for (int j = 0; j < columnCount(); j++) {
            if (nullptr != getCell(i, j)) {
                delete getCell(i, j);
            }
            InventoryCell* cell = new InventoryCell(nullptr, 0);
            setCell(cell, i, j);
        }
    }
    if (rowCount()>0 && columnCount()>0) {
        setMaximumHeight(rowCount()*cellHeight+rowCount()-1);
        setMinimumHeight(rowCount()*cellHeight+rowCount()-1);
        setMaximumWidth(columnCount()*cellWidth+columnCount()-1);
        setMinimumWidth(columnCount()*cellWidth+columnCount()-1);
    }

    horizontalHeader()->setDefaultSectionSize(100);
    verticalHeader()->setDefaultSectionSize(100);

    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
}

void Inventory::saveToBD() {
    DBAdapter *adapter = DBAdapter::getInstance();
    for (int i = 0; i < rowCount(); i++) {
        for (int j = 0; j < columnCount(); j++) {
            InventoryCell* crCell = getCell(i, j);
            if (nullptr != crCell) {
                adapter->insertOrUpdateInventory(crCell->getType(),crCell->getCount(),(i*columnCount()) + j);
            }
        }
    }
}

void Inventory::loadFromBD() {
    if (columnCount()>0 && rowCount()>0) {

        DBAdapter *adapter = DBAdapter::getInstance();
        QList<ItemRecord> record_list = adapter->getInventory();

        for(auto it = record_list.begin(); it != record_list.end(); ++it) {
            setCell(new InventoryCell(ItemFactory::createItem(it->type, nullptr), it->count), (it->id)%rowCount(), (it->id) / rowCount() );
        }
        repaintAllCells();
    }
}

void Inventory::refreshCell(int x, int y) {
    DBAdapter *adapter = DBAdapter::getInstance();
    InventoryCell* crCell = getCell(x, y);
    if (nullptr != crCell) {
        adapter->insertOrUpdateInventory(crCell->getType(),crCell->getCount(),(y*rowCount()) + x);
    }
}

QPoint Inventory::getIndex(QPoint pos) {
    if ((pos.x() < columnCount() * cellWidth + DELTA_X) && (pos.y() < rowCount() * cellHeight + DELTA_Y)) {
        return QPoint((pos.y() - DELTA_Y)/cellHeight, (pos.x() - DELTA_X)/cellWidth);
    }
    return QPoint(-1, -1);
}

void Inventory::repaintAllCells() {
    InventoryCell* cell=nullptr;
    for (int i = 0; i < rowCount(); i++) {
        for (int j = 0; j < columnCount(); j++) {
            cell = getCell(i, j);
            if (nullptr != cell) {
                cell->repaint();
            }
        }
    }
}

void Inventory::newGame() {
    for (int i = 0; i < columnCount(); i++) {
        for (int j = 0; j < rowCount(); j++) {
            InventoryCell* cell = new InventoryCell(nullptr, 0);
            setCell(cell, i, j);
        }
    }
    saveToBD();
}
