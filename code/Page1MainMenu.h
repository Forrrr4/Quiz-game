#ifndef PAGE1MAINMENU_H
#define PAGE1MAINMENU_H

#include <QWidget>

namespace Ui {
class Page1MainMenu;
}

class Page1MainMenu : public QWidget {
    Q_OBJECT

public:
    explicit Page1MainMenu(QWidget *parent = nullptr);
    ~Page1MainMenu();

signals:
    void guessPlayerClicked();
    void guessHeroClicked();

private:
    Ui::Page1MainMenu *ui;
};

#endif // PAGE1MAINMENU_H
