#include "mainmenuwidget.h"

#include <QSpacerItem>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QPainter>

MainMenuWidget::MainMenuWidget(QWidget *parent): QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setMinimumHeight(32);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setMargin(0);

    QPushButton* newGameButton = new QPushButton(tr("New game"));
    connect(newGameButton, &QPushButton::clicked, this, &MainMenuWidget::newGameSignal);

    QPushButton* exitButton = new QPushButton(tr("Exit"));
    connect(exitButton, &QPushButton::clicked, this, &MainMenuWidget::exitSignal);

    QIcon icon(":/images/btn_close.png");
    QToolButton* closeButton = new QToolButton();
    closeButton->setIcon(icon);
    connect(closeButton, &QToolButton::clicked, this, &MainMenuWidget::closeSignal);

    horizontalLayout->addStretch();
    horizontalLayout->addWidget(newGameButton);
    horizontalLayout->addStretch();
    horizontalLayout->addWidget(exitButton);
    horizontalLayout->addStretch();
    horizontalLayout->addWidget(closeButton);
}

MainMenuWidget::~MainMenuWidget() {
}
