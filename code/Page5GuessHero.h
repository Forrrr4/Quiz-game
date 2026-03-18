#ifndef PAGE5GUESSHERO_H
#define PAGE5GUESSHERO_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include<QTextEdit>
#include "PlayerDataStorage.h"
class Page5GuessHero : public QWidget {
    Q_OBJECT
public:
    explicit Page5GuessHero(QWidget *parent = nullptr);
    void initGameHero() {
        using namespace PlayerDataStorage;
        attempts = 0;
        guessHistory.clear();

        int idx = rand() % heroList.size();
        targetId = heroList[idx].getid();
        appendResult("🎯 已选择目标选手，开始游戏！");
    }
    void setMaxTries(int x){maxTries=x;}
    int getMaxTries(){return maxTries;}
    void resetGameState();
    void updateInfoText(const QString& message);
private:
    QLineEdit *inputLineEdit;
    QPushButton *guessButton;
    QPushButton *giveUpButton;
    QPushButton *EasyButton;
    QPushButton *MiddleButton;
    QPushButton *HardButton;
    QTextEdit* infoTextEdit;
    QListWidget *resultListWidget;
    int maxTries = 6;
    int attempts = 0;
    std::string targetId;
    std::vector<std::string> guessHistory;
    bool gameOver = false;
private slots:
    void onGuessButtonClicked();
    void onGiveUpButtonClicked();
    void onEasyButtonClicked();
    void onMiddleButtonClicked();
    void onHardButtonClicked();

public:
    void appendResult(const QString &text);
    QString getUserInput() const;
};

#endif // PAGE5GUESSHERO_H
