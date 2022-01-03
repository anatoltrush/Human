#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>

#include "Entities/AbstractHuman.h"
#include "Entities/CutSurface.h"

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

    man::CutSurface cutSurface;

private:
    Ui::MainWindow *ui;
    QTimer *timer = nullptr;

private slots:
    void updUi();
};

#endif // MAINWINDOW_H
