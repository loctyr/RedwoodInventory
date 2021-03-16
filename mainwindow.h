#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainMenuWidget;

/**
 * @brief The MainWindow class - class of main window with all GUI
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief MainWindow - create window with mainMenuWidget, twInventory, inventoryItem, buttons
     * @param parent - the parent widget
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    /**
     * @brief on_newGameButton_clicked - the slot of button ("New game") from mainMenuWidget.
     */
    void on_newGameButton_clicked();

    /**
     * @brief on_exitButton_clicked - the slot of button ("Exit") from mainMenuWidget
     */
    void on_exitButton_clicked();

private slots:
    /**
     * @brief on_mainMenuButton_clicked - the slot of button ("Main menu")
     */
    void on_pbMainMenu_clicked();

protected:
    /**
     * @brief moveEvent - override method for moving mainMenuWidget
     * @param event - the event of move
     */
    void moveEvent(QMoveEvent *event) override;

    /**
     * @brief closeEvent - override method for resize mainMenuWidget
     * @param event - the event of close
     */
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::MainWindow *ui;
    MainMenuWidget* mainMenuWidget;

    /**
     * @brief setMainMenuGeometry - method to change size and position of mainMenuWidget
     * @param event - the event of close
     */
    void setMainMenuGeometry();
};
#endif // MAINWINDOW_H
