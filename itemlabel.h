#ifndef ITEMLABEL_H
#define ITEMLABEL_H

#include <QObject>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QDebug>
#include <QScopedPointer>

#include "item.h"

/**
 * @brief The Item class - class of any item of inventory
 */
class ItemLabel : public QLabel {
    Q_OBJECT

public:
    /**
     * @brief Item - create object
     * @param item_ - pointer to item
     * @param parent_ - the parent Widget
     */
    explicit ItemLabel(Item* item, QWidget *parent = NULL);

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
     * @brief dropEvent - override drop drag.
     * @param event - the event of drag drop
     */
    void dropEvent(QDropEvent *event) override;

    /**
     * @brief mousePressEvent - override mousePress. Setting MimeData in format : ("source" + count + type).
     * @param event - the event of press mouse
     */
    void mousePressEvent(QMouseEvent *event) override;

     QScopedPointer<Item> item; //! item type
};

#endif // ITEMLABEL_H
