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

/**
 * @brief The Inventory class - the class of inventory. Consists of cells (InventoryCell)
 */
class Inventory : public QTableWidget {
    Q_OBJECT
public:
    /**
     * @brief Inventory - create inventory (QTableWidget) with this size.
     * @param rows - the count of rows for inventory
     * @param columns - the count of columns for inventory
     * @param parent - the parent Widget
     */
    explicit Inventory(int rows, int columns, QWidget *parent = 0);

    /**
     * @brief Inventory - create inventory (QTableWidget) with this size. Filling this by cells (InventoryCell)
     * @param rows - the count of rows for inventory
     * @param columns - the count of columns for inventory
     * @param parent - the parent Widget
     */
    explicit Inventory(QWidget *parent = 0);
    ~Inventory();

    /**
     * @brief setRowCount - Sets the number of rows in this inventory to rows.
     * @param rows - the count of rows for inventory
     */
    void setRowCount(int rows);

    /**
     * @brief Inventory - Sets the number of columns in this inventory to columns.
     * @param columns - the count of columns for inventory
     */
    void setColumnCount(int columns);

    /**
     * @brief refreshCell - refreshing inventory's cell with this coordinates
     * @param x - x coordinate of cell
     * @param y - y coordinate of cell
     */
    void refreshCell(int x, int y);

    /**
     * @brief saveToBD - saving full Inventory to DataBase by adapter (DBAdapter).
     */
    void saveToBD();

    /**
     * @brief loadFromBD - load full Inventory from DataBase by adapter (DBAdapter)
     */
    void loadFromBD();

    /**
     * @brief newGame - reset Inventory for new game.
     */
    void newGame();

protected:
    /**
     * @brief dragEnterEvent - override drag enter.
     * @param event - the event of enter drag
     */
    void dragEnterEvent(QDragEnterEvent *event) override;

    /**
     * @brief dragLeaveEvent - override drag leave.
     * @param event - the event of leave drag
     */
    void dragLeaveEvent(QDragLeaveEvent *event) override;

    /**
     * @brief dragMoveEvent - override drag move.
     * @param event - the event of move drag
     */
    void dragMoveEvent(QDragMoveEvent *event) override;

    /**
     * @brief dropEvent - override drop drag. Parsing MimeData in format : (("from inventory" + QPoint)/("source" + count + type))
     * @param event - the event of drag drop
     */
    void dropEvent(QDropEvent *event) override;

    /**
     * @brief mousePressEvent - override mousePress. Setting MimeData in format : ("from inventory" + QPoint). For Right Mouse Button - item->removeAction()  (playSound for appleItem)
     * @param event - the event of press mouse
     */
    void mousePressEvent(QMouseEvent *event) override;

private:
    /**
     * @brief init - Filling inventory
     * @param rows - the count of rows for inventory
     * @param columns - the count of columns for inventory
     * @param parent - the parent Widget
     */
    void init();

    /**
     * @brief getCell - getting inventory cell with this coordinates.
     * @param x - the x coordinate of cell
     * @param y - the y coordinate of cell
     * @return - the pointer on cell with this coordinates
     */
    InventoryCell* getCell(int x, int y);

    /**
     * @brief setCell - delete old cell and setting cell with this cell and this coordinates
     * @param cell - the new cell for setting
     * @param x - the x coordinates for setting
     * @param y - the y coordinates for setting
     */
    void setCell(InventoryCell* cell, int x, int y);

    /**
     * @brief getIndex - getting coordinates of cell, that contain this point
     * @param pos - the position of point in cell (or not)
     * @return (0 <= x < rowCount, 0 <= y < columnCount), where x,y - coordinates of cell - if inventory contain this point
     *             (x = -1, y = -1) - if inventory don't contain this point
     */
    QPoint getIndex(QPoint pos);

    /**
     * @brief repaintAllCells - repaint all cells of Inventory
     */
    void repaintAllCells();
};

#endif // INVENTORY_H
