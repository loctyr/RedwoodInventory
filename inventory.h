#ifndef INVENTORY_H
#define INVENTORY_H
#include <QObject>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QList>
#include <QDebug>
#include <QHeaderView>
#include "appleitem.h"
#include "dbadapter.h"
#include "inventorycell.h"
#define DELTA_X 0
#define DELTA_Y 0

/**
 * @brief The Inventory class - the class of inventory. Consists of cells (InventoryCell)
 */
class Inventory : public QTableWidget {
    Q_OBJECT
public:
    explicit Inventory(int rows, int columns, QWidget *parent = 0);
    explicit Inventory(QWidget *parent = 0);
    ~Inventory();

    void setRowCount(int rows);
    void setColumnCount(int columns);

    void refreshCell(int x, int y);
    void saveToBD();
    void loadFromBD();
    void newGame();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void init();
    InventoryCell* getCell(int x, int y);
    void setCell(InventoryCell* cell, int x, int y);
    QPoint getIndex(QPoint pos);
    void repaintAllCells();

    int verticalSize;
    int horizontalSize;
};

#endif // INVENTORY_H
