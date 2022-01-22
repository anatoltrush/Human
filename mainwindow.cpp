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
    /*ui->widgetGL->cyborg->skeleton->rotateBonesSingle(ui->widgetGL->cyborg->skeleton->bones["RightHand"], man::Angle(-0.2f, 0.0f, 0.0f));
    ui->widgetGL->cutSuface.execute(ui->widgetGL->cyborg->skeleton);
    ui->widgetGL->update();*/
    //ui->l_triangles->setText("Tri: " + QString::number(human->skeleton->bones["Skull"]->stlObject.triangles.size()));
}

void MainWindow::on_pB_Cut_clicked()
{
    bool isWarn = false;
    if(ui->widgetGL->cyborg)
        ui->widgetGL->cutSuface.execute(ui->widgetGL->cyborg->skeleton, isWarn);
    if(ui->widgetGL->human)
        ui->widgetGL->cutSuface.execute(ui->widgetGL->human->skeleton, isWarn);
    ui->widgetGL->update();

    if(isWarn)
        ui->pB_Cut->setStyleSheet("background-color: yellow");
    else
        ui->pB_Cut->setStyleSheet("background-color: green");
}


void MainWindow::on_pB_CutUp_clicked()
{
    for(auto &pt : ui->widgetGL->cutSuface.surface.vertex)
        pt.setZ(pt.z() + 5.0f);
    ui->widgetGL->update();
}


void MainWindow::on_pB_CutDown_clicked()
{
    for(auto &pt : ui->widgetGL->cutSuface.surface.vertex)
        pt.setZ(pt.z() - 4.0f);
    ui->widgetGL->update();
}


void MainWindow::on_pB_Srlzd_clicked()
{    
#ifdef _WIN64
    man::Status serC = ui->widgetGL->cyborg->serialize("D:\\");
    man::Status serH = ui->widgetGL->human->serialize("D:\\STL\\");
#else
    //man::Status ser = ui->widgetGL->human->serialize("/home/atrush/Desktop/PROJECTS/StLiGr/garbage/");
    man::Status ser = ui->widgetGL->cyborg->serialize("/home/atrush/Desktop/PROJECTS/StLiGr/garbage/");
#endif
    ui->pB_Srlzd->setText("Ser = " + QString::number(serC) + " | " + QString::number(serH));
}

void MainWindow::on_pB_ReArr_clicked()
{
    man::Status resArrange =
            reArranger.reArrange(*ui->widgetGL->human, *ui->widgetGL->cyborg);

    if(resArrange == man::StatusOk)
        ui->pB_ReArr->setStyleSheet("background-color: green");
    else
        ui->pB_ReArr->setStyleSheet("background-color: yellow");

    ui->widgetGL->update();
}
