#ifndef APPLEITEM_H
#define APPLEITEM_H

#include <QObject>
#include <QtMultimedia/QMediaPlayer>
#include "item.h"

class AppleItem : public Item {
public:
    AppleItem(QWidget* parent = NULL);

    void removeAction() override;
};

#endif // APPLEITEM_H
