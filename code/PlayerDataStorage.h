#ifndef PLAYER_DATA_STORAGE_H
#define PLAYER_DATA_STORAGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Character.h"

using namespace std;

namespace PlayerDataStorage {

inline vector<LOLPlayer> lolPlayers;
inline vector<CSPlayer> csPlayers;
inline vector<Hero> heroList;

inline vector<string> parseCSVLine(const string& line) {
    vector<string> result;
    bool inQuotes = false;
    string field;

    for (char ch : line) {
        if (ch == '"') {
            inQuotes = !inQuotes;
        } else if (ch == ',' && !inQuotes) {
            result.push_back(field);
            field.clear();
        } else {
            field += ch;
        }
    }
    result.push_back(field);
    return result;
}

inline vector<string> splitHistory(const string& historyField) {
    vector<string> result;
    stringstream ss(historyField);
    string item;
    while (getline(ss, item, ',')) {
        size_t start = item.find_first_not_of(" ");
        size_t end = item.find_last_not_of(" ");
        if (start != string::npos && end != string::npos)
            result.push_back(item.substr(start, end - start + 1));
    }
    return result;
}

inline void readLOLPlayers(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "无法打开 " << filename << " 文件" << endl;
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        vector<string> fields = parseCSVLine(line);
        if (fields.size() != 10) {
            cerr << "LOL玩家数据格式错误，字段数不正确，当前字段数：" << fields.size() << endl;
            continue;
        }

        try {
            string id = fields[0];
            int age = stoi(fields[1]);
            string currentTeam = fields[2];
            vector<string> history = splitHistory(fields[3]);
            string area = fields[4];
            string position = fields[5];
            string birthplace = fields[6];
            string status = fields[7];
            int frequency = stoi(fields[8]);
            int champions = stoi(fields[9]);

            LOLPlayer player(id, age, currentTeam, history, birthplace, status, area, position, frequency, champions);
            lolPlayers.push_back(player);
        } catch (const exception& e) {
            cerr << "LOL玩家数据解析错误：" << e.what() << endl;
        }
    }
    fin.close();
}

inline void readCSPlayers(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "无法打开 " << filename << " 文件" << endl;
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        vector<string> fields = parseCSVLine(line);
        if (fields.size() != 8) {
            cerr << "CS玩家数据格式错误，字段数不正确，当前字段数：" << fields.size() << endl;
            continue;
        }

        try {
            string id = fields[0];
            int age = stoi(fields[1]);
            string currentTeam = fields[2];
            vector<string> history = splitHistory(fields[3]);
            string birthplace = fields[4];
            string status = fields[5];
            int MVP = stoi(fields[6]);
            int highestTop = stoi(fields[7]);

            CSPlayer player(id, age, currentTeam, history, birthplace, "未知", MVP, highestTop);
            csPlayers.push_back(player);
        } catch (const exception& e) {
            cerr << "CS玩家数据解析错误：" << e.what() << endl;
        }
    }
    fin.close();
}

inline void readHeros(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "无法打开英雄数据文件: " << filename << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        vector<string> fields = parseCSVLine(line);
        if (fields.size() != 8) {
            cerr << "英雄数据格式错误，字段数应为8，当前为: " << fields.size() << endl;
            continue;
        }

        try {
            string title = fields[0];               // 称号作为ID
            string name = fields[1];                // 英雄名字
            vector<string> types = splitHistory(fields[2]); // 拆分类型，如"法师,刺客"
            string manaType = fields[3];            // 法力类型
            int attackRange = stoi(fields[4]);      // 攻击距离
            string releaseDate = fields[5];         // 发布时间
            string position = fields[6];            // 位置
            string faction = fields[7];             // 阵营

            Hero hero(title, name, types, manaType, attackRange, releaseDate, position, faction);
            heroList.push_back(hero);
            cout << "已加载英雄: " << title << " (ID: " << hero.getid() << ")" << endl;
        } catch (const exception& e) {
            cerr << "英雄数据解析错误: " << e.what() << endl;
        }
    }

    cout << "总共加载了 " << heroList.size() << " 个英雄" << endl;
    fin.close();
}
}

#endif // PLAYER_DATA_STORAGE_H
