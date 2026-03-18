#include "Page1MainMenu.h"
#include "ui_Page1MainMenu.h"
#include "PlayerGuessGame.h"

Page1MainMenu::Page1MainMenu(QWidget *parent)
    : QWidget(parent), ui(new Ui::Page1MainMenu) {
    ui->setupUi(this);
    connect(ui->btnGuessPlayer, &QPushButton::clicked, this, &Page1MainMenu::guessPlayerClicked);
    connect(ui->btnGuessHero, &QPushButton::clicked, this, &Page1MainMenu::guessHeroClicked);

}

Page1MainMenu::~Page1MainMenu() {
    delete ui;
}
