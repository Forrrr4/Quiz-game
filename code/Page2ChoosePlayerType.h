#ifndef PAGE2CHOOSEPLAYERTYPE_H
#define PAGE2CHOOSEPLAYERTYPE_H

#include <QWidget>

namespace Ui {
class Page2ChoosePlayerType;
}

class Page2ChoosePlayerType : public QWidget {
    Q_OBJECT

public:
    explicit Page2ChoosePlayerType(QWidget *parent = nullptr);
    ~Page2ChoosePlayerType();

signals:
    void lolClicked();
    void csClicked();

private:
    Ui::Page2ChoosePlayerType *ui;
};

#endif // PAGE2CHOOSEPLAYERTYPE_H
