#ifndef WIDGETGL_H
#define WIDGETGL_H

#include <QtGui>
#include <QOpenGLWidget>

#include "Entities/AbstractHuman.h"
#include "Entities/CutSurface.h"

class WidgetGL : public QOpenGLWidget
{
public:
    WidgetGL(QWidget *parent = 0);

    man::Angle rotation;
    QVector3D scale;
    QVector3D constScale;
    QVector3D koeff;
    QPoint mousePos; // переменная для запоминания позиции нажатия мышки

    QSize prevSize;

    man::AbstractHuman* human = nullptr;
    man::AbstractHuman* cyborg = nullptr;
    man::CutSurface cutSuface;

    void drawAxis();

protected:
    void initializeGL() override; // reimplementation
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* pe) override;   // нажатие на клавишу мыши
    void mouseMoveEvent(QMouseEvent* pe) override;    // перемещение мыши
    void mouseReleaseEvent(QMouseEvent* pe) override; // отжатие клавиши мыши
    void wheelEvent(QWheelEvent *pe) override;
};

#endif // WIDGETGL_H
