#include "appleitem.h"
#include <QtMultimedia/QMediaPlayer>

AppleItem::AppleItem(QWidget* parent) : Item("Apple", parent) {
    setAttribute(Qt::WA_DeleteOnClose);
}

void AppleItem::removeAction() {
    QMediaPlayer* player = new QMediaPlayer();
    player->setMedia(QMediaContent(QUrl(getSoundPath())));
    player->play();
}
