#ifndef PAGE4GUESSCS_H
#define PAGE4GUESSCS_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include<QTextEdit>
#include "PlayerDataStorage.h"
class Page4GuessCS : public QWidget {
    Q_OBJECT
public:
    explicit Page4GuessCS(QWidget *parent = nullptr);
    void initGameCS() {
        using namespace PlayerDataStorage;
        attempts = 0;
        guessHistory.clear();

        int idx = rand() % csPlayers.size();
        targetId = csPlayers[idx].getid();
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

#endif // PAGE3GUESSCS_H
