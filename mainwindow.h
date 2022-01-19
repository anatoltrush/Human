#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>

#include "Entities/AbstractHuman.h"
#include "Algorithms/ReArranger.h"

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

    man::ReArranger reArranger;

private slots:
    void updUi();
    void on_pB_Cut_clicked();
    void on_pB_CutUp_clicked();
    void on_pB_CutDown_clicked();
    void on_pB_Srlzd_clicked();
    void on_pB_ReArr_clicked();
};

#endif // MAINWINDOW_H
