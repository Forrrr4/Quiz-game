#ifndef CHARACTER_H
#define CHARACTER_H

#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 基类 Character
class Character {
protected:
    string id;

public:
    Character() = default;
    Character(const string& id) : id(id) {}
    virtual ~Character() = default;

    void setid(const string& _id) { id = _id; }
    string getid() const { return id; }

    // 新增纯虚函数，强制派生类实现多态比较
    virtual void compareWith(const Character& other) const = 0;
};

// 派生类 Player（从 Character 派生）
class Player : public Character {
protected:
    int age;
    string team;
    vector<string> historyTeam;
    string birthplace;
    string status;

public:
    Player() = default;
    Player(const string& id, int age, const string& team,
           const vector<string>& historyTeam,
           const string& birthplace, const string& status)
        : Character(id), age(age), team(team), historyTeam(historyTeam),
        birthplace(birthplace), status(status) {}

    int getAge() const { return age; }
    void setAge(int a){ age = a; }
    string getTeam() const { return team; }
    string getBirthplace() const { return birthplace; }
    string getStatus() const { return status; }
    const vector<string>& getHistoryTeam() const { return historyTeam; }

    // 重写基类的纯虚函数，参数改为基类引用方便多态
    virtual void compareWith(const Character& other) const override = 0;

    void printHistoryTeam() const {
        cout << "历史战队: ";
        for (const string& t : historyTeam) {
            cout << t << " ";
        }
        cout << endl;
    }
};

// LOLPlayer 从 Player 派生
class LOLPlayer : public Player {
private:
    string Competition_Area;
    string position;
    int Frequency;
    int champions;

public:
    LOLPlayer(const string& id, int age, const string& team,
              const vector<string>& historyTeam, const string& birthplace,
              const string& status, const string& Competition_Area,
              const string& position, int Frequency, int champions)
        : Player(id, age, team, historyTeam, birthplace, status),
        Competition_Area(Competition_Area), position(position),
        Frequency(Frequency), champions(champions) {}

    string getCompetitionArea() const { return Competition_Area; }
    string getPosition() const { return position; }
    int getFrequency() const { return Frequency; }
    int getChampions() const { return champions; }

    void compareWith(const Character& other) const override {
        const LOLPlayer* p = dynamic_cast<const LOLPlayer*>(&other);
        if (!p) {
            cout << "无法比较：类型不匹配" << endl;
            return;
        }

        cout << left;
        cout << setw(10) << "年龄: " << setw(10) << getAge();
        if (getAge() == p->getAge()) cout << " √";
        cout << endl;

        cout << setw(10) << "战队: " << setw(10) << getTeam();
        if (getTeam() == p->getTeam()) cout << " √";
        cout << endl;

        cout << "历史战队: ";
        for (const auto& team : getHistoryTeam()) {
            bool matched = false;
            for (const auto& otherTeam : p->getHistoryTeam()) {
                if (team == otherTeam) {
                    matched = true;
                    break;
                }
            }
            cout << team << (matched ? " √ " : " × ");
        }
        cout << endl;

        cout << setw(10) << "赛区: " << setw(10) << getCompetitionArea();
        if (getCompetitionArea() == p->getCompetitionArea()) cout << " √";
        cout << endl;

        cout << setw(10) << "位置: " << setw(10) << getPosition();
        if (getPosition() == p->getPosition()) cout << " √";
        cout << endl;

        cout << setw(10) << "出生地: " << setw(10) << getBirthplace();
        if (getBirthplace() == p->getBirthplace()) cout << " √";
        cout << endl;

        cout << setw(10) << "状态: " << setw(10) << getStatus();
        if (getStatus() == p->getStatus()) cout << " √";
        cout << endl;

        cout << setw(10) << "出场频率: " << setw(10) << getFrequency();
        if (getFrequency() == p->getFrequency()) cout << " √";
        cout << endl;

        cout << setw(10) << "冠军数: " << setw(10) << getChampions();
        if (getChampions() == p->getChampions()) cout << " √";
        cout << endl;
    }
};

// CSPlayer 从 Player 派生
class CSPlayer : public Player {
private:
    int MVP;
    int highestTop;

public:
    CSPlayer(const string& id, int age, const string& team,
             const vector<string>& historyTeam, const string& birthplace,
             const string& status, int MVP, int highestTop)
        : Player(id, age, team, historyTeam, birthplace, status),
        MVP(MVP), highestTop(highestTop) {}

    int getMVP() const { return MVP; }
    int getHighestTop() const { return highestTop; }

    void compareWith(const Character& other) const override {
        const CSPlayer* p = dynamic_cast<const CSPlayer*>(&other);
        if (!p) {
            cout << "无法比较：类型不匹配" << endl;
            return;
        }

        cout << left;
        cout << setw(10) << "年龄: " << setw(10) << getAge();
        if (getAge() == p->getAge()) cout << " √";
        cout << endl;

        cout << setw(10) << "战队: " << setw(10) << getTeam();
        if (getTeam() == p->getTeam()) cout << " √";
        cout << endl;

        cout << "历史战队: ";
        for (const auto& team : getHistoryTeam()) {
            bool matched = false;
            for (const auto& otherTeam : p->getHistoryTeam()) {
                if (team == otherTeam) {
                    matched = true;
                    break;
                }
            }
            cout << team << (matched ? " √ " : " × ");
        }
        cout << endl;

        cout << setw(10) << "出生地: " << setw(10) << getBirthplace();
        if (getBirthplace() == p->getBirthplace()) cout << " √";
        cout << endl;

        cout << setw(10) << "状态: " << setw(10) << getStatus();
        if (getStatus() == p->getStatus()) cout << " √";
        cout << endl;

        cout << setw(10) << "MVP次数: " << setw(10) << getMVP();
        if (getMVP() == p->getMVP()) cout << " √";
        cout << endl;

        cout << setw(10) << "最高排名: " << setw(10) << getHighestTop();
        if (getHighestTop() == p->getHighestTop()) cout << " √";
        cout << endl;
    }
};

// Hero 从 Character 派生
class Hero : public Character {
private:
    string name;
    vector<string> types;
    string adaptivePower;
    int attackRange;
    string releaseDate;
    string position;
    string faction;

public:
    Hero() = default;

    Hero(const string& id, const string& name,
         const vector<string>& types,
         const string& adaptivePower,
         int attackRange,
         const string& releaseDate,
         const string& position,
         const string& faction)
        : Character(id), name(name), types(types),
        adaptivePower(adaptivePower), attackRange(attackRange),
        releaseDate(releaseDate), position(position), faction(faction) {}

    string getName() const { return name; }
    vector<string> getTypes() const { return types; }
    string getAdaptivePower() const { return adaptivePower; }
    int getAttackRange() const { return attackRange; }
    string getReleaseDate() const { return releaseDate; }
    string getPosition() const { return position; }
    string getFaction() const { return faction; }

    void compareWith(const Character& other) const override {
        const Hero* p = dynamic_cast<const Hero*>(&other);
        if (!p) {
            cout << "无法比较：类型不匹配" << endl;
            return;
        }

        cout << "比较英雄：" << name << " 和 " << p->name << endl;

        cout << "类型: ";
        for (const auto& t : types) cout << t << " ";
        cout << " vs ";
        for (const auto& t : p->types) cout << t << " ";
        cout << endl;

        cout << "法力类型: " << adaptivePower << " vs " << p->adaptivePower << endl;
        cout << "攻击距离: " << attackRange << " vs " << p->attackRange << endl;
        cout << "发布日期: " << releaseDate << " vs " << p->releaseDate << endl;
        cout << "位置: " << position << " vs " << p->position << endl;
        cout << "阵营: " << faction << " vs " << p->faction << endl;
    }
};

#endif // CHARACTER_H
