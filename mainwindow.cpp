#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer();
    timer->setInterval(100); // Задаем интервал таймера
    connect(timer, SIGNAL(timeout()), this, SLOT(updUi())); // Подключаем сигнал таймера к нашему слоту
    timer->start(); // Запускаем таймер
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setHuman(man::AbstractHuman *human)
{
    ui->widgetGL->human = human;
}

void MainWindow::setCyborg(man::AbstractHuman *cyborg)
{
    ui->widgetGL->cyborg = cyborg;
}

void MainWindow::updUi()
{
    //ui->widgetGL->cyborg->skeleton->rotateBonesSingle(ui->widgetGL->cyborg->skeleton->bones["RightHand"], man::Angle(-0.2f, 0.0f, 0.0f));
    //ui->widgetGL->cutSuface.execute(ui->widgetGL->cyborg->skeleton);
    //ui->widgetGL->update();
    //ui->l_triangles->setText("Tri: " + QString::number(humanAbs->skeleton->bones["Skull"]->stlObject.triangles.size()));
}

void MainWindow::on_pB_Cut_clicked()
{
    if(ui->widgetGL->cyborg)
        ui->widgetGL->cutSuface.execute(ui->widgetGL->cyborg->skeleton);
    if(ui->widgetGL->human)
        ui->widgetGL->cutSuface.execute(ui->widgetGL->human->skeleton);
    ui->widgetGL->update();
}


void MainWindow::on_pB_CutUp_clicked()
{
    for(auto &pt : ui->widgetGL->cutSuface.surface.vertex)
        pt.z += 5;
    ui->widgetGL->update();
}


void MainWindow::on_pB_CutDown_clicked()
{
    for(auto &pt : ui->widgetGL->cutSuface.surface.vertex)
        pt.z -= 4;
    ui->widgetGL->update();
}

