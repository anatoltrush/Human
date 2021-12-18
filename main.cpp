#include <iostream>

#include "mainwindow.h"
#include <QApplication>

using namespace std;

#include "Human.h"
#include "Cyborg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;    

    man::Human human;
    cout << "S human: " + to_string(sizeof(human)) << endl;
    man::Cyborg cyborg;
    cout << "S cyborg: " + to_string(sizeof(cyborg)) << endl;
    cyborg.skeleton.bones[boneHead].serialize();

    w.show();
    return a.exec();
}
