#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenuwidget.h"
#include "dbadapter.h"
#include "itemfactory.h"
#include "item.h"

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

    DBAdapter* adapter = DBAdapter::getInstance();
    QStringList typeList = adapter->getAllItemTypes();
    for(auto& type : typeList) {
        Item* ptr = ItemFactory::createItem(type, ui->wRight);
        if (nullptr != ptr) {
            if (nullptr != ui->wRight->layout()) {
                ui->wRight->layout()->addWidget(ptr);
            }
        }
    }
    ui->twInventory->acceptDrops();

    //QPixmap pixmap(ui->lbApple->getImagePath());
    //ui->lbApple->setPixmap(pixmap);
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
