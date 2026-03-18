#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    stack = new QStackedWidget(this);
    page1 = new Page1MainMenu(this);
    page2 = new Page2ChoosePlayerType(this);
    page3 = new Page3GuessLOL(this);
    page4 = new Page4GuessCS(this);
    page5 = new Page5GuessHero(this);

    stack->addWidget(page1); // 0
    stack->addWidget(page2); // 1
    stack->addWidget(page3); // 2
    stack->addWidget(page4); // 3
    stack->addWidget(page5); // 4

    ui->verticalLayout->addWidget(stack); // ui中预设verticalLayout

    // 连接按钮跳转
    connect(page1, &Page1MainMenu::guessPlayerClicked, this, &Widget::goToPage2);
    connect(page1, &Page1MainMenu::guessHeroClicked, this, &Widget::goToPage5);
    connect(page2, &Page2ChoosePlayerType::lolClicked, this, &Widget::goToPage3);
    connect(page2, &Page2ChoosePlayerType::csClicked, this, &Widget::goToPage4);
}

Widget::~Widget() {
    delete ui;
}

void Widget::goToPage2() {
    PlayerGuessGame::gameState.mainMode = 1;
    stack->setCurrentWidget(page2)    ;
    qDebug() << "切换到猜选手页面，mainMode =" << PlayerGuessGame::gameState.mainMode;}
void Widget::goToPage5() {
    PlayerGuessGame::gameState.mainMode = 2;
    stack->setCurrentWidget(page5);
    qDebug() << "切换到猜英雄页面，mainMode =" << PlayerGuessGame::gameState.mainMode;
    page5->initGameHero();
    }
void Widget::goToPage3() {
    PlayerGuessGame::gameState.subMode=1;
    stack->setCurrentWidget(page3);
    page3->initGameLOL();}
void Widget::goToPage4() {
    PlayerGuessGame::gameState.subMode=2;
    stack->setCurrentWidget(page4);
    page4->initGameCS(); }
