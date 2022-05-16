#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QTcpSocket>
#include <QMainWindow>
#include <QHostAddress>

#include <thread>

#include "Entities/AbstractHuman.h"
#include "Algorithms/CyberReArranger.h"
#include "Algorithms/MediaPipeReArranger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setHuman(man::AbstractHuman* human);
    void setCyborg(man::AbstractHuman* cyborg);    

private:
    Ui::MainWindow *ui;
    QTimer *timer = nullptr;

    // --- thread ---
    uint32_t delay_ms = 1000;
    bool isRcvRunning = true;
    std::thread thr_rcv;
    void threadRcv();

    // --- SERVER DATA ---
    const QString serverMessage = "GET";
    QTcpSocket *tcpSocket;    
    std::vector<QVector3D> vecData3D;

private slots:
    void slotConnected();
    void slotReadyRead();
    void slotDisConnected();

    void updUi();
    void on_pB_Cut_clicked();
    void on_pB_CutUp_clicked();
    void on_pB_CutDown_clicked();
    void on_pB_Srlzd_clicked();
    void on_pB_CybReArr_clicked();
    void on_pB_Table_clicked();
    void on_pB_MPReArr_clicked();
    void on_pB_zmq_clicked();
};

#endif // MAINWINDOW_H
