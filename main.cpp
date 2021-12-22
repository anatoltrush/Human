#include <iostream>

#include "mainwindow.h"
#include <QApplication>

using namespace std;

#include "Human.h"
#include "Cyborg.h"
#include "Config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;    

    man::Config config;
    int loadConf = config.loadConfigData();

    man::Human human;
    int loadHumSkel = human.skeleton->loadFromJson(config);
    int conHumSkel = human.skeleton->construct();
    cout << "S human: " + to_string(sizeof(human)) << endl;

    man::Cyborg cyborg;
    int loadCybSkel = cyborg.skeleton->loadFromJson(config);
    int conCybSkel = cyborg.skeleton->construct();
    cout << "S cyborg: " + to_string(sizeof(cyborg)) << endl;
    cyborg.skeleton->bones["Skull"]->serialize();

    w.show();
    return a.exec();
}
