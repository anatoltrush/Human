#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>

#include "Cyborg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    man::Cyborg* cyborg = nullptr;

private:
    Ui::MainWindow *ui;
    QTimer *timer = nullptr;

private slots:
    void updUi();
};

#endif // MAINWINDOW_H
