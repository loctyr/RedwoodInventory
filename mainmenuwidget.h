#ifndef MAIN_MENU_WIDGET_H
#define MAIN_MENU_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class MainMenuWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainMenuWidget(QWidget *parent = 0);
    ~MainMenuWidget();
signals:
    void newGameSignal();
    void exitSignal();
};

#endif // MAIN_MENU_WIDGET_H
