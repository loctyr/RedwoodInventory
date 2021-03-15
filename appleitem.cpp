#include "appleitem.h"

AppleItem::AppleItem(QWidget* parent) : Item("Apple", parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    //setPixmap(QPixmap(getImagePath()));//устанавливаем тут поскольку в конструкторе базового класса getImagePath еще недоступна
}

void AppleItem::removeAction() {
    QMediaPlayer* player = new QMediaPlayer();
    player->setMedia(QMediaContent(QUrl::fromLocalFile(getSoundPath())));
    player->play();
}
