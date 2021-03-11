#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenuwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainMenuWidget = new MainMenuWidget(this);
    connect(mainMenuWidget, &MainMenuWidget::newGameSignal, this, &MainWindow::on_newGameButton_clicked);
    connect(mainMenuWidget, &MainMenuWidget::exitSignal, this, &MainWindow::on_exitButton_clicked);

    setAcceptDrops(true);
    on_pbMainMenu_clicked();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newGameButton_clicked() {
    mainMenuWidget->close();
    this->setEnabled(true);
}

void MainWindow::on_exitButton_clicked() {
    this->close();
}

void MainWindow::on_pbMainMenu_clicked() {
    setMainMenuGeometry();
    mainMenuWidget->show();
    this->setEnabled(false);
    mainMenuWidget->setEnabled(true);
}

void MainWindow::moveEvent(QMoveEvent */*event*/) {
    setMainMenuGeometry();
}

void MainWindow::resizeEvent(QResizeEvent */*event*/) {
    setMainMenuGeometry();
}

void MainWindow::setMainMenuGeometry() {
    QRect parentRect = this->geometry();
    mainMenuWidget->resize(parentRect.width(), 25);
    mainMenuWidget->move(parentRect.left(), parentRect.top());
}
