#ifndef PLAYER_GUESS_GAME_H
#define PLAYER_GUESS_GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>  // setw
#include "PlayerDataStorage.h"

namespace PlayerGuessGame {

using namespace std;
using namespace PlayerDataStorage;

struct GameState {
    int mainMode = 0;    // 1 = 猜选手，2 = 猜英雄
    int subMode = 0;     // 1 = LOL，2 = CS
    int maxTries = 0;
    int currentTry = 0;
    int targetIndex = -1;
    string targetId;
    string targetName;
    vector<string> history;
    bool isCorrect = false;

};
extern GameState gameState;
// 英文字符串转小写（仅用于选手id等英文字符串）
inline string toLower(const string& s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(),
              [](unsigned char c){ return tolower(c); });
    return res;
}

// 判断选手库中是否有对应id（英文，用toLower忽略大小写）
template<typename PlayerType>
inline bool containsPlayer(const vector<PlayerType>& players, const string& inputId) {
    string inputLower = toLower(inputId);
    for (const auto& player : players) {
        string playerId = toLower(player.getid());
        if (playerId == inputLower) {
            return true;
        }
    }
    return false;
}

// 根据id查找选手指针（英文）
template<typename PlayerType>
inline const PlayerType* findPlayerById(const vector<PlayerType>& players, const string& inputId) {
    string inputLower = toLower(inputId);
    for (const auto& player : players) {
        if (toLower(player.getid()) == inputLower) {
            return &player;
        }
    }
    return nullptr;
}

// 判断英雄库中是否有对应id或name（均为英文，忽略大小写）
inline bool containsHero(const vector<Hero>& heros, const string& input) {
    string inputLower = toLower(input);
    for (const auto& hero : heros) {
        if (toLower(hero.getid()) == inputLower || toLower(hero.getName()) == inputLower) {
            return true;
        }
    }
    return false;
}

// 根据输入查找英雄，支持id或name（均英文，忽略大小写）
inline const Hero* findHeroByIdOrName(const vector<Hero>& heros, const string& input) {
    string inputLower = toLower(input);
    for (const auto& hero : heros) {
        if (toLower(hero.getid()) == inputLower || toLower(hero.getName()) == inputLower) {
            return &hero;
        }
    }
    return nullptr;
}

// ---------------------------------------
// 格式化对比辅助函数

inline string compareIntArrow(int guessVal, int targetVal) {
    if (guessVal > targetVal) return to_string(guessVal) + " ↑";
    else if (guessVal < targetVal) return to_string(guessVal) + " ↓";
    else return to_string(guessVal);
}

inline string compareDoubleArrow(double guessVal, double targetVal, int precision = 2) {
    std::ostringstream oss;
    oss << fixed << setprecision(precision) << guessVal;
    if (guessVal > targetVal) return oss.str() + " ↑";
    else if (guessVal < targetVal) return oss.str() + " ↓";
    else return oss.str();
}


inline string compareStringArrow(const string& guessStr, const string& targetStr) {
    if (guessStr == targetStr) return guessStr;
    else return guessStr + " (不同)";
}

// 对比箭头（整型）
inline string cmpArrow(int a, int b) {
    if (a > b) return "↓";
    if (a < b) return "↑";
    return "=";
}

// 对比箭头（字符串日期）
inline string cmpDate(const string& a, const string& b) {
    if (a > b) return "↓";
    if (a < b) return "↑";
    return "=";
}

// 相等标记
inline string cmpMark(const string& a, const string& b) {
    return a == b ? "√" : "";
}

// vector<string> 转字符串
inline string vectorToStringWithMark(const vector<string>& guessTypes, const vector<string>& targetTypes) {
    string result;
    for (const auto& type : guessTypes) {
        result += type;
        if (std::find(targetTypes.begin(), targetTypes.end(), type) != targetTypes.end()) {
            result += "√";
        }
        result += ",";
    }
    if (!result.empty()) result.pop_back(); // 移除最后一个逗号
    return result;
}

// ---------------------------------------
// LOLPlayer 对比输出（示例字段，按需调整）

inline void printLOLPlayerHeader() {
    cout << left
         << setw(10) << "ID"
         << setw(10)  << "年龄"
         << setw(20)  << "赛区"
         << setw(20)  << "位置"
         << setw(20)  << "出生地"
         << setw(20)  << "状态"
         << setw(20) << "世界赛次数"
         << setw(20) << "冠军数"
         << setw(30) << "战队"
         << setw(100) << "历史战队"<< endl;
    cout << setfill('-') << setw(129) << "-" << setfill(' ') << endl;
}


inline void printLOLPlayerCompare(const LOLPlayer& guess, const LOLPlayer& target) {
    // 字段宽度定义
    const int ID_WIDTH = 10;
    const int AGE_WIDTH = 10;
    const int AREA_WIDTH = 20;
    const int POS_WIDTH = 20;
    const int BIRTH_WIDTH = 20;
    const int STATUS_WIDTH = 20;
    const int TIMES_WIDTH = 20;
    const int CHAMP_WIDTH = 20;
    const int TEAM_WIDTH = 30;
    const int HISTORY_WIDTH = 100;

    // 比较符号辅助函数
    auto cmpArrow = [](int a, int b) {
        if (a > b) return "↓";
        if (a < b) return "↑";
        return "=";
    };
    auto cmpMark = [](const string& a, const string& b) {
        return a == b ? "√" : "";
    };

    stringstream line1;

    // ID
    line1 << left << setw(ID_WIDTH) << guess.getid();

    // 年龄 + 箭头
    string ageWithArrow = to_string(guess.getAge()) + cmpArrow(guess.getAge(), target.getAge());
    line1 << setw(AGE_WIDTH - 1) << left << ageWithArrow;

    // 赛区 + 判断符号
    string areaWithMark = guess.getCompetitionArea() + cmpMark(guess.getCompetitionArea(), target.getCompetitionArea());
    line1 << setw(AREA_WIDTH - 1) << left << areaWithMark;

    // 位置 + 判断符号
    string posWithMark = guess.getPosition() + cmpMark(guess.getPosition(), target.getPosition());
    line1 << setw(POS_WIDTH - 1) << left << posWithMark;

    // 出生地 + 判断符号
    string birthWithMark = guess.getBirthplace() + cmpMark(guess.getBirthplace(), target.getBirthplace());
    line1 << setw(BIRTH_WIDTH - 1) << left << birthWithMark;

    // 状态 + 判断符号
    string statusWithMark = guess.getStatus() + cmpMark(guess.getStatus(), target.getStatus());
    line1 << setw(STATUS_WIDTH - 1) << left << statusWithMark;

    // 世界赛次数 + 箭头
    string freqWithArrow = to_string(guess.getFrequency()) + cmpArrow(guess.getFrequency(), target.getFrequency());
    line1 << setw(TIMES_WIDTH - 1) << left << freqWithArrow;

    // 冠军数 + 箭头
    string champWithArrow = to_string(guess.getChampions()) + cmpArrow(guess.getChampions(), target.getChampions());
    line1 << setw(CHAMP_WIDTH - 1) << left << champWithArrow;

    // 战队 + 判断符号（移到最后）
    string teamWithMark = guess.getTeam() + cmpMark(guess.getTeam(), target.getTeam());
    line1 << setw(TEAM_WIDTH - 1)  << left << teamWithMark;

    // 历史战队
    string histLine;
    for (const auto& t : guess.getHistoryTeam()) {
        histLine += t;
        for (const auto& tt : target.getHistoryTeam()) {
            if (t == tt) {
                histLine += "√";
                break;
            }
        }
        histLine += " ";
    }
    line1 << setw(HISTORY_WIDTH) << left << histLine;

    // 输出整行
    cout << line1.str() << endl;
}
// ---------------------------------------
// CSPlayer 对比输出（示例字段）

inline void printCSPlayerHeader() {
    cout << left
         << setw(10) << "ID"
         << setw(10) << "年龄"
         << setw(15) << "MVP次数"
         << setw(15) << "最高排名"
         << setw(20) << "战队"
         << setw(40) << "历史战队"
         << endl;
    cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
}

inline void printCSPlayerCompare(const CSPlayer& guess, const CSPlayer& target) {
    const int ID_WIDTH = 10;
    const int AGE_WIDTH = 10;
    const int TEAM_WIDTH = 20;
    const int HISTORY_WIDTH = 40;
    const int MVP_WIDTH = 15;
    const int RANK_WIDTH = 15;

    // 比较辅助函数
    auto cmpArrow = [](int a, int b) {
        if (a > b) return "↓";
        if (a < b) return "↑";
        return "=";
    };
    auto cmpMark = [](const string& a, const string& b) {
        return a == b ? "√" : "";
    };

    stringstream line1;

    // ID
    line1 << left << setw(ID_WIDTH) << guess.getid();

    // 年龄 + 箭头
    string ageWithArrow = to_string(guess.getAge()) + cmpArrow(guess.getAge(), target.getAge());
    line1 << setw(AGE_WIDTH - 1) << ageWithArrow;

    // 战队 + 判断符号
    string teamWithMark = guess.getTeam() + cmpMark(guess.getTeam(), target.getTeam());
    line1 << setw(TEAM_WIDTH - 1) << teamWithMark;

    // 历史战队（带 √）
    string histLine;
    for (const auto& t : guess.getHistoryTeam()) {
        histLine += t;
        for (const auto& tt : target.getHistoryTeam()) {
            if (t == tt) {
                histLine += "√";
                break;
            }
        }
        histLine += " ";
    }
    line1 << setw(HISTORY_WIDTH) << histLine;

    // MVP 次数 + 箭头
    string mvpWithArrow = to_string(guess.getMVP()) + cmpArrow(guess.getMVP(), target.getMVP());
    line1 << setw(MVP_WIDTH - 1) << mvpWithArrow;

    // 最高排名 + 箭头
    string rankWithArrow = to_string(guess.getHighestTop()) + cmpArrow(guess.getHighestTop(), target.getHighestTop());
    line1 << setw(RANK_WIDTH - 1) << rankWithArrow;

    // 输出行
    cout << line1.str() << endl;
}

// ---------------------------------------
// Hero 对比输出

inline void printHeroHeader() {
    cout << left
         << setw(40) << "ID"           // 减小宽度
         << setw(30) << "名称"
         << setw(30) << "类型"
         << setw(30) << "适应之力"
         << setw(30) << "攻击距离"
         << setw(30) << "发布日期"
         << setw(30) << "位置"
         << setw(30) << "阵营"
         << endl;
    cout << setfill('-') << setw(105) << "-" << setfill(' ') << endl;  // 调整分隔线长度
}

inline void printHeroCompare(const Hero& guess, const Hero& target, ostream& out = cout) {
    stringstream line;
    const int ID_WIDTH = 40;           // 减小宽度
    const int NAME_WIDTH = 30;
    const int Type_WIDTH = 30;
    const int Adaptive_WIDTH = 30;
    const int Attack_WIDTH = 30;
    const int Day_WIDTH = 30;
    const int Position_WIDTH = 30;
    const int X_WIDTH = 30;

    // ID
    line << left << setw(ID_WIDTH) << guess.getid();

    // 名称
    line<< left << setw(NAME_WIDTH) << guess.getName();

    // 类型（vector）对比
    string typesStr = vectorToStringWithMark(guess.getTypes(), target.getTypes());
    line<< left << setw(Type_WIDTH) << typesStr;

    // 适应之力+ 箭头
    string adaptiveWithArrow = guess.getAdaptivePower() + cmpMark(guess.getAdaptivePower(), target.getAdaptivePower());
    if (adaptiveWithArrow.length() > Adaptive_WIDTH - 2) {
        adaptiveWithArrow = adaptiveWithArrow.substr(0, Adaptive_WIDTH - 3) + "...";
    }
    line<< left << setw(Adaptive_WIDTH) << adaptiveWithArrow;

    // 攻击距离（int）+ 箭头
    string rangeWithArrow = to_string(guess.getAttackRange()) + cmpArrow(guess.getAttackRange(), target.getAttackRange());
    line<< left << setw(Attack_WIDTH) << rangeWithArrow;

    // 发布日期（string）+ ↑↓
    string dateWithArrow = guess.getReleaseDate() + cmpDate(guess.getReleaseDate(), target.getReleaseDate());
    if (dateWithArrow.length() > Day_WIDTH - 2) {
        dateWithArrow = dateWithArrow.substr(0, Day_WIDTH - 3) + "...";
    }
    line<< left << setw(Day_WIDTH) << dateWithArrow;

    // 位置（string）+ √
    string posWithMark = guess.getPosition() + cmpMark(guess.getPosition(), target.getPosition());
    if (posWithMark.length() > Position_WIDTH - 2) {
        posWithMark = posWithMark.substr(0, Position_WIDTH - 3) + "...";
    }
    line<< left << setw(Position_WIDTH) << posWithMark;

    // 阵营（string）+ √
    string factionWithMark = guess.getFaction() + cmpMark(guess.getFaction(), target.getFaction());
    if (factionWithMark.length() > X_WIDTH - 2) {
        factionWithMark = factionWithMark.substr(0, X_WIDTH - 3) + "...";
    }
    line<< left << setw(X_WIDTH) << factionWithMark;

    // 输出结果到传入的流
    out << line.str() << endl;
}

// ---------------------------------------



// 主游戏函数

inline GameState gameState;

inline bool initGuessGame(int mainMode, int subMode = 0) {
    gameState = GameState();  // 重置
    gameState.mainMode = mainMode;
    gameState.subMode = subMode;

    if (mainMode == 1 && subMode == 1 && lolPlayers.empty()) return false;
    if (mainMode == 1 && subMode == 2 && csPlayers.empty()) return false;
    if (mainMode == 2 && heroList.empty()) return false;

    srand(static_cast<unsigned int>(time(nullptr)));
    if (mainMode == 1) {
        if (subMode == 1) {
            gameState.targetIndex = rand() % lolPlayers.size();
            gameState.targetId = lolPlayers[gameState.targetIndex].getid();
        } else {
            gameState.targetIndex = rand() % csPlayers.size();
            gameState.targetId = csPlayers[gameState.targetIndex].getid();
        }
    } else {
        gameState.targetIndex = rand() % heroList.size();
        gameState.targetId = heroList[gameState.targetIndex].getid();
        gameState.targetName = heroList[gameState.targetIndex].getName();
    }

    return true;
}

inline void setMaxTries(int tries) {
    gameState.maxTries = tries;
}

inline string makeGuess(const string& guess) {
    if (gameState.currentTry >= gameState.maxTries || gameState.isCorrect) return "游戏已结束。";

    stringstream output;
    bool correct = false;
    bool found = false;

    if (gameState.mainMode == 1) {
        found = (gameState.subMode == 1) ? containsPlayer(lolPlayers, guess) : containsPlayer(csPlayers, guess);
    } else {
        found = containsHero(heroList, guess);
    }

    if (!found) {
        output << "错误：未找到该ID或名称！";
        return output.str();
    }

    gameState.currentTry++;

    if (gameState.mainMode == 1) {
        if (toLower(guess) == toLower(gameState.targetId)) correct = true;
    } else {
        if (toLower(guess) == toLower(gameState.targetId) ||
            toLower(guess) == toLower(gameState.targetName)) correct = true;
    }

    if (correct) {
        gameState.isCorrect = true;
        output << "🎉 猜对了！答案是: " << gameState.targetId;
        if (gameState.mainMode == 2) output << "（名称: " << gameState.targetName << "）";
    } else {
        output << "❌ 猜错了！你还有 " << (gameState.maxTries - gameState.currentTry) << " 次机会。\n";
        output << "【对比信息】\n";

        if (gameState.mainMode == 1) {
            if (gameState.subMode == 1) {
                const LOLPlayer* guessPlayer = findPlayerById(lolPlayers, guess);
                const LOLPlayer* answerPlayer = &lolPlayers[gameState.targetIndex];
                if (guessPlayer) {
                    stringstream ss;
                    streambuf* old = cout.rdbuf(ss.rdbuf());
                    printLOLPlayerCompare(*guessPlayer, *answerPlayer);
                    cout.rdbuf(old);
                    gameState.history.push_back(ss.str());
                    output << ss.str();
                }
            } else {
                const CSPlayer* guessPlayer = findPlayerById(csPlayers, guess);
                const CSPlayer* answerPlayer = &csPlayers[gameState.targetIndex];
                if (guessPlayer) {
                    stringstream ss;
                    streambuf* old = cout.rdbuf(ss.rdbuf());
                    printCSPlayerCompare(*guessPlayer, *answerPlayer);
                    cout.rdbuf(old);
                    gameState.history.push_back(ss.str());
                    output << ss.str();
                }
            }
        } else {
            const Hero* guessHero = findHeroByIdOrName(heroList, guess);
            const Hero* answerHero = &heroList[gameState.targetIndex];
            if (guessHero) {
                stringstream ss;
                streambuf* old = cout.rdbuf(ss.rdbuf());
                printHeroCompare(*guessHero, *answerHero);
                cout.rdbuf(old);
                gameState.history.push_back(ss.str());
                output << ss.str();
            }
        }
    }

    return output.str();
}

inline bool isGameOver() {
    return gameState.isCorrect || gameState.currentTry >= gameState.maxTries;
}

inline string getFinalAnswer() {
    stringstream ss;
    ss << "正确答案是 " << gameState.targetId;
    if (gameState.mainMode == 2)
        ss << "（名称: " << gameState.targetName << "）";
    return ss.str();
}

inline const vector<string>& getHistory() {
    return gameState.history;
}
}

 // namespace PlayerGuessGame

#endif // PLAYER_GUESS_GAME_H
