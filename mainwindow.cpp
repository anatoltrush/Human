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

    int colCount = 2;
    ui->tabProp->setShowGrid(true);
    ui->tabProp->setColumnCount(colCount);
    ui->tabProp->setHorizontalHeaderLabels(QStringList() << "Property" << "Value");
    ui->tabProp->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    bool isWarn = false;
    ui->widgetGL->cutSuface.execute(ui->widgetGL->cyborg->skeleton, isWarn);
    ui->widgetGL->update();*/
    //ui->l_triangles->setText("Tri: " + QString::number(human->skeleton->bones["Skull"]->stlObject.triangles.size()));
}

void MainWindow::on_pB_Cut_clicked()
{
    //man::AbstractSkeleton* ccc1 = ui->widgetGL->cyborg->skeleton;
    //man::AbstractSkeleton* hhh1 = ui->widgetGL->human->skeleton;

    bool isWarn = false;
    if(ui->widgetGL->cyborg)
        ui->widgetGL->cutSuface.execute(ui->widgetGL->cyborg->skeleton, isWarn);
    // ---
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
    for(auto &pt : ui->widgetGL->cutSuface.planeSurface.vertex)
        pt.setZ(pt.z() + 5.0f);
    ui->widgetGL->update();
}


void MainWindow::on_pB_CutDown_clicked()
{
    for(auto &pt : ui->widgetGL->cutSuface.planeSurface.vertex)
        pt.setZ(pt.z() - 4.0f);
    ui->widgetGL->update();
}


void MainWindow::on_pB_Srlzd_clicked()
{    
#ifdef _WIN64
    man::Status serC = ui->widgetGL->cyborg->serialize("D:\\");
    man::Status serH = ui->widgetGL->human->serialize("D:\\STL\\");
#else
    man::Status serH; // = ui->widgetGL->human->serialize("/home/atrush/Desktop/PROJECTS/StLiGr/garbage/");
    man::Status serC = ui->widgetGL->cyborg->serialize("/home/atrush/Desktop/PROJECTS/StLiGr/garbage/");
#endif
    ui->pB_Srlzd->setText("Ser = " + QString::number(serC) + " | " + QString::number(serH));
}

void MainWindow::on_pB_CybReArr_clicked()
{
    ui->widgetGL->human->skeleton->rotateBonesSingle(ui->widgetGL->human->skeleton->bones["LeftHand"], man::Angle(2.0f, 1.0f, 0.5f));

    man::CyberReArranger reArranger;
    man::Status resArrange = reArranger.reArrange(*ui->widgetGL->human, *ui->widgetGL->cyborg);

    man::AbstractSkeleton* ccc = ui->widgetGL->cyborg->skeleton;
    man::AbstractSkeleton* hhh = ui->widgetGL->human->skeleton;

    if(resArrange == man::StatusOk)
        ui->pB_CybReArr->setStyleSheet("background-color: green");
    else
        ui->pB_CybReArr->setStyleSheet("background-color: yellow");

    on_pB_Cut_clicked();

    ui->widgetGL->update();
}

void MainWindow::on_pB_Table_clicked()
{
    man::AbstractBone* obj = ui->widgetGL->cyborg->skeleton->bones["RightHand"];
    QMap<QString, QVariant> properties = obj->getPropertyList();

    ui->tabProp->clear();
    ui->tabProp->setRowCount(properties.size());
    int rawN = 0;
    for(auto it = properties.begin(); it != properties.end(); it++){
        QTableWidgetItem* itemK = new QTableWidgetItem();
        itemK->setText(it.key());

        QTableWidgetItem* itemV = new QTableWidgetItem();
        itemV->setText(it.value().toString());

        ui->tabProp->setItem(rawN, 0, itemK);
        ui->tabProp->setItem(rawN, 1, itemV);

        rawN++;
    }
}

void MainWindow::on_pB_MPReArr_clicked()
{
    man::MediaPipeReArranger mpReArranger;
    mpReArranger.anchorPoints.insert("LeftShoulder", QVector3D(-50.0f, -12.0f, 5.0f));
    mpReArranger.anchorPoints.insert("RightKnee", QVector3D(40.0f, -5.0f, 70.0f));
    mpReArranger.anchorPoints.insert("Abra", QVector3D(-501.0f, -121.0f, 51.0f));
    man::Status resArrange = mpReArranger.reArrange(*ui->widgetGL->human);

    if(resArrange == man::StatusOk)
        ui->pB_MPReArr->setStyleSheet("background-color: green");
    else
        ui->pB_MPReArr->setStyleSheet("background-color: yellow");

    //on_pB_Cut_clicked();

    ui->widgetGL->update();
}
