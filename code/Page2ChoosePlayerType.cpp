#include "Page2ChoosePlayerType.h"
#include "ui_Page2ChoosePlayerType.h"

Page2ChoosePlayerType::Page2ChoosePlayerType(QWidget *parent)
    : QWidget(parent), ui(new Ui::Page2ChoosePlayerType) {
    ui->setupUi(this);
    connect(ui->btnLOL, &QPushButton::clicked, this, &Page2ChoosePlayerType::lolClicked);
    connect(ui->btnCS, &QPushButton::clicked, this, &Page2ChoosePlayerType::csClicked);
}

Page2ChoosePlayerType::~Page2ChoosePlayerType() {
    delete ui;
}
