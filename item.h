#ifndef ITEM_H
#define ITEM_H

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

/**
 * @brief The Item class - class of any item of inventory
 */
class Item : public QLabel {
    Q_OBJECT

public:
    /**
     * @brief Item - create object
     * @param type_ - type of item
     * @param parent_ - the parent Widget
     */
    explicit Item(QString type_, QWidget *parent = NULL);

    /**
     * @brief getType - virtual method for getting type of inventory object
     * @return - type of inventory object
     */
    virtual QString getType();

    /**
     * @brief getImagePath - virtual method for getting path of image of this inventory object
     * @return - the path of picture file
     */
    virtual QString getImagePath();

    /**
     * @brief getSoundPath - virtual method for getting path of sound of this inventory object
     * @return - the path of sound file
     */
    virtual QString getSoundPath();

    /**
     * @brief removeAction - virtual method, that performed action of using item (playing sound)
     */
    virtual void removeAction() = 0;

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

    QString type; //! item type
};

#endif // ITEM_H
