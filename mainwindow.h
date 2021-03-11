#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainMenuWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void on_newGameButton_clicked();
    void on_exitButton_clicked();

private slots:
    void on_pbMainMenu_clicked();

protected:
    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::MainWindow *ui;
    MainMenuWidget* mainMenuWidget;

    void setMainMenuGeometry();
};
#endif // MAINWINDOW_H
