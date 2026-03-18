#include "widget.h"
#include <QApplication>
#include <iostream>
#include <QDir>
#include "PlayerDataStorage.h"
#include "PlayerGuessGame.h"


using namespace std;
using namespace PlayerDataStorage;
using namespace PlayerGuessGame;


int main(int argc, char *argv[]) {
    qDebug() << "Current working directory:" << QDir::currentPath();
    readLOLPlayers("lolplayers.txt");
    readCSPlayers("csplayer.txt");
    readHeros("heros.txt");

    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}
