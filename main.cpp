#include <iostream>

#include "mainwindow.h"
#include <QApplication>

using namespace std;

#include "Entities/Human.h"
#include "Entities/Cyborg.h"
#include "Config/Config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;    

    man::Config config;
    int loadConf = config.loadConfigData();

    man::Human human;
    int loadHumSkel = human.skeleton->loadFromJson(config, true);
    int conHumSkel = human.skeleton->construct();
    //cout << "Size human bone: " + to_string(sizeof(human)) << endl;

    man::Cyborg cyborg;
    int loadCybSkel = cyborg.skeleton->loadFromJson(config, false);
    int conCybSkel = cyborg.skeleton->construct();
    //cout << "Size cyberbone: " + to_string(sizeof(cyborg.skeleton->bones["Skull"])) << endl;
    cout << "AbsBone: " + to_string(sizeof(man::AbstractBone)) << endl;

    w.cyborg = &cyborg;

    w.show();
    return a.exec();
}
