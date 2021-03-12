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

class Item : public QLabel {
    Q_OBJECT

public:
    explicit Item(QString type_, QWidget *parent = NULL);
    virtual QString getType();
    virtual QString getImagePath();

    virtual QString getSoundPath();
    virtual void removeAction() = 0;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    QString type;
    QString imagePath;
};

#endif // ITEM_H
