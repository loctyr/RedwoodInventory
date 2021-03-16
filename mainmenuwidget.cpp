#include "mainmenuwidget.h"

#include <QSpacerItem>
#include <QPushButton>
#include <QHBoxLayout>

MainMenuWidget::MainMenuWidget(QWidget *parent): QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_UnderMouse);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setMargin(0);

    QPushButton* newGameButton = new QPushButton(tr("New game"));
    connect(newGameButton, &QPushButton::clicked, this, &MainMenuWidget::newGameSignal);

    QPushButton* exitButton = new QPushButton(tr("Exit"));
    connect(exitButton, &QPushButton::clicked, this, &MainMenuWidget::exitSignal);

    horizontalLayout->addStretch();
    horizontalLayout->addWidget(newGameButton);
    horizontalLayout->addStretch();
    horizontalLayout->addWidget(exitButton);
    horizontalLayout->addStretch();
}

MainMenuWidget::~MainMenuWidget() {
}
