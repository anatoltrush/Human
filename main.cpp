#include <iostream>

#include "mainwindow.h"
#include <QApplication>

using namespace std;

#include "Entities/Human.h"
#include "Entities/Cyborg.h"
#include "Config/Defines.h"
#include "Config/Config.h"
#include "Aux/ExtraMath.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;    

    man::Config config;
    man::Status loadConf = config.loadConfigData();

    man::Human human;
    man::Status loadHumSkel = human.skeleton->loadFromJson(config);
    man::Status conHumSkel = human.skeleton->construct();

    man::Cyborg cyborg;
    man::Status loadCybSkel = cyborg.skeleton->loadFromJson(config);
    man::Status conCybSkel = cyborg.skeleton->construct();
    cout << "AbsBone: " + to_string(sizeof(man::AbstractBone)) << endl;

    if(conCybSkel == man::StatusOk){w.setCyborg(&cyborg);}
    if(conHumSkel == man::StatusOk){w.setHuman(&human);}

    QMap<QString, QVariant> props = cyborg.getPropertyList();

    w.show();
    return a.exec();
}
