#include "appleitem.h"
#include <QtMultimedia/QMediaPlayer>

AppleItem::AppleItem() : Item("Apple") {
}

void AppleItem::removeAction() {
    QMediaPlayer* player = new QMediaPlayer();
    player->setMedia(QMediaContent(QUrl(getSoundPath())));
    player->play();
}
