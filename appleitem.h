#ifndef APPLEITEM_H
#define APPLEITEM_H

#include "item.h"

/**
 * @brief The AppleItem class - class of Apple, that describes apple label in main window.
 * inherits Item.
 */
class AppleItem : public Item {
public:
    /**
     * @brief AppleItem - create AppleItem - new Label with Apple
     */
    AppleItem();

    /**
     * @brief removeAction - the action, that was performed when apple was used in Incentory (right mouse button). Played sound of apple.
     */
    void removeAction() override;
};

#endif // APPLEITEM_H
