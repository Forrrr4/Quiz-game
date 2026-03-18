#include "Page3GuessLOL.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>

// 引入你已有的数据和工具函数
#include "PlayerDataStorage.h"
#include "PlayerGuessGame.h"

using namespace PlayerDataStorage;
using namespace PlayerGuessGame;

Page3GuessLOL::Page3GuessLOL(QWidget *parent) : QWidget(parent) {
    inputLineEdit = new QLineEdit(this);
    guessButton = new QPushButton("猜一下", this);
    giveUpButton = new QPushButton("投降", this);
    resultListWidget = new QListWidget(this);
    infoTextEdit = new QTextEdit(this);
    infoTextEdit->setReadOnly(true);  // 设置只读，避免用户编辑
    infoTextEdit->setFixedHeight(60); // 控制高度，避免太占空间
    infoTextEdit->setStyleSheet("background-color: #f0f0f0;"); // 可选美化



    EasyButton = new QPushButton("Easy (10次)", this);
    MiddleButton = new QPushButton("Mid (7次)", this);
    HardButton = new QPushButton("Hard (5次)", this);

    auto *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(inputLineEdit);
    inputLayout->addWidget(guessButton);
    inputLayout->addWidget(giveUpButton);
    inputLayout->addWidget(infoTextEdit);
    auto *difficultyLayout = new QHBoxLayout;
    difficultyLayout->addWidget(EasyButton);
    difficultyLayout->addWidget(MiddleButton);
    difficultyLayout->addWidget(HardButton);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(difficultyLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(resultListWidget);

    setLayout(mainLayout);

    connect(guessButton, &QPushButton::clicked, this, &Page3GuessLOL::onGuessButtonClicked);
    connect(giveUpButton, &QPushButton::clicked, this, &Page3GuessLOL::onGiveUpButtonClicked);
    connect(EasyButton, &QPushButton::clicked, this, &Page3GuessLOL::onEasyButtonClicked);
    connect(MiddleButton, &QPushButton::clicked, this, &Page3GuessLOL::onMiddleButtonClicked);
    connect(HardButton, &QPushButton::clicked, this, &Page3GuessLOL::onHardButtonClicked);
    connect(inputLineEdit, &QLineEdit::textEdited, this, [=](const QString &) {
        if (gameOver) {
            resetGameState();  // 自动重启
            gameOver = false;
        }
    });
    maxTries = 10;
    appendResult("🎮 当前难度: Easy，最大猜测次数: 10");
}

void Page3GuessLOL::onEasyButtonClicked() {
    maxTries = 10;
    appendResult("🎮 设置难度为 Easy，最大猜测次数: 10");
    // 你可以选择这里重置游戏状态
}

void Page3GuessLOL::onMiddleButtonClicked() {
    maxTries = 7;
    appendResult("🎮 设置难度为 Mid，最大猜测次数: 7");
}

void Page3GuessLOL::onHardButtonClicked() {
    maxTries = 5;
    appendResult("🎮 设置难度为 Hard，最大猜测次数: 5");
}

void Page3GuessLOL::onGuessButtonClicked() {
    static bool firstGuess = true;
    if (firstGuess) {
        firstGuess = false;
        EasyButton->setEnabled(false);
        MiddleButton->setEnabled(false);
        HardButton->setEnabled(false);
    }
    using namespace PlayerDataStorage;

    QString qinput = inputLineEdit->text().trimmed();
    std::string guess = qinput.toStdString();
    inputLineEdit->clear();

    if (guess.empty()) return;

    // 判断是否在选手库中
    if (!containsPlayer(lolPlayers, guess)) {
        appendResult("❌ 错误：未找到该ID或名称，请重新输入！");
        return;
    }

    // 判断是否猜中
    if (toLower(guess) == toLower(targetId)) {
        appendResult("🎉 猜对了！答案是: " + QString::fromStdString(targetId));
        giveUpButton->setEnabled(false);
        gameOver = true;
        return;
    }

    attempts++;
    int remaining = maxTries - attempts;
    updateInfoText("❌ 猜错了！你还有 " + QString::number(remaining) + " 次机会。");

    const LOLPlayer* guessPlayer = findPlayerById(lolPlayers, guess);
    const LOLPlayer* answerPlayer = findPlayerById(lolPlayers, targetId);

    if (guessPlayer && answerPlayer) {
        std::stringstream ss;
        streambuf* old_buf = std::cout.rdbuf(ss.rdbuf());

        printLOLPlayerHeader();
        printLOLPlayerCompare(*guessPlayer, *answerPlayer);
        std::cout.rdbuf(old_buf);

        guessHistory.push_back(ss.str());
        appendResult("📊 对比结果：");
        for (const auto& history : guessHistory) {
            appendResult(QString::fromStdString(history));
        }
    }

    if (attempts >= maxTries) {
        updateInfoText("💀 游戏结束！");
        appendResult("正确答案是: " + QString::fromStdString(targetId));
        guessButton->setEnabled(false);
        inputLineEdit->setEnabled(false);
        giveUpButton->setEnabled(false);
        gameOver = true;
    }
}

void Page3GuessLOL::appendResult(const QString &text) {
    resultListWidget->addItem(text);
    resultListWidget->scrollToBottom();
}
void Page3GuessLOL::onGiveUpButtonClicked() {
    // 示例：给出提示，可以根据需要修改
    updateInfoText("👋 你选择了投降，游戏结束！");
    gameOver = true;
}
void Page3GuessLOL::resetGameState() {
    inputLineEdit->clear();
    resultListWidget->clear();
    guessHistory.clear();
    attempts = 0;

    inputLineEdit->setEnabled(true);
    guessButton->setEnabled(true);
    EasyButton->setEnabled(true);
    MiddleButton->setEnabled(true);
    HardButton->setEnabled(true);
}
void Page3GuessLOL::updateInfoText(const QString& message) {
    QString info = "剩余次数: " + QString::number(maxTries - attempts) + "\n" + message;
    infoTextEdit->setText(info);
}
