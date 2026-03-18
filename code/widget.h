#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>

#include "Page1MainMenu.h"
#include "Page2ChoosePlayerType.h"
#include "Page3GuessLOL.h"
#include "Page4GuessCS.h"
#include "Page5GuessHero.h"
#include <QDebug>
#include "PlayerGuessGame.h"
using namespace PlayerGuessGame;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void goToPage2();
    void goToPage5();
    void goToPage3();
    void goToPage4();

private:
    Ui::Widget *ui;
    QStackedWidget *stack;

    Page1MainMenu *page1;
    Page2ChoosePlayerType *page2;
    Page3GuessLOL *page3;
    Page4GuessCS *page4;
    Page5GuessHero *page5;
};

#endif // WIDGET_H
