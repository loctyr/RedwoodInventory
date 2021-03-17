#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenuwidget.h"
#include "dbadapter.h"
#include "itemfactory.h"
#include "item.h"
#include "itemlabel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainMenuWidget = new MainMenuWidget(centralWidget());
    connect(mainMenuWidget, &MainMenuWidget::newGameSignal, this, &MainWindow::on_newGameButton_clicked);
    connect(mainMenuWidget, &MainMenuWidget::exitSignal, this, &MainWindow::on_exitButton_clicked);
    connect(mainMenuWidget, &MainMenuWidget::closeSignal, this, &MainWindow::on_closeButton_clicked);

    setAcceptDrops(true);
    on_pbMainMenu_clicked();

    DBAdapter* adapter = DBAdapter::getInstance();
    QStringList typeList = adapter->getAllItemTypes();
    for(auto& type : typeList) {
        ItemLabel* ptr = new ItemLabel(ItemFactory::createItem(type), ui->wRight);
        if ((nullptr != ptr) && (nullptr != ui->wRight->layout()) ) {
            ui->wRight->layout()->addWidget(ptr);
        }
    }
    ui->twInventory->loadFromBD();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_newGameButton_clicked() {
    mainMenuWidget->close();
    setEnabled(true);
    ui->twInventory->newGame();
}

void MainWindow::on_exitButton_clicked() {
    close();
}

void MainWindow::on_closeButton_clicked() {
    mainMenuWidget->close();
    setEnabled(true);
}

void MainWindow::on_pbMainMenu_clicked() {
    setMainMenuGeometry();
    mainMenuWidget->show();
    setEnabled(false);
    mainMenuWidget->setEnabled(true);
}

void MainWindow::moveEvent(QMoveEvent */*event*/) {
    setMainMenuGeometry();
}

void MainWindow::resizeEvent(QResizeEvent */*event*/) {
    setMainMenuGeometry();
}

void MainWindow::setMainMenuGeometry() {
    QRect parentRect = geometry();
    mainMenuWidget->resize(parentRect.width(), 25);
    mainMenuWidget->move(parentRect.left(), parentRect.top());
}
