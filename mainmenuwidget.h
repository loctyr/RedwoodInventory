#ifndef MAIN_MENU_WIDGET_H
#define MAIN_MENU_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

/**
 * @brief The MainMenuWidget class - the class of mainMenu with buttons ("New game", "Exit")
 */
class MainMenuWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief MainMenuWidget - create MainMenuWidget
     * @param parent - the parent widget (MainWindow)
     */
    explicit MainMenuWidget(QWidget *parent = 0);
    ~MainMenuWidget();
signals:
    /**
     * @brief newGameSignal - the signal of new game. sending to MainWindow
     */
    void newGameSignal();

    /**
     * @brief exitSignal - the signal of exit game
     */
    void exitSignal();
};

#endif // MAIN_MENU_WIDGET_H
