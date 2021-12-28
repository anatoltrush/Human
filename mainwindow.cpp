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

void MainWindow::setHuman(man::AbstractHuman *absHhuman)
{
    ui->widgetGL->humanAbs = absHhuman;
}

void MainWindow::updUi()
{
    //ui->l_triangles->setText("Tri: " + QString::number(humanAbs->skeleton->bones["Skull"]->stlObject.triangles.size()));
}
