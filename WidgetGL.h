#ifndef WIDGETGL_H
#define WIDGETGL_H

#include <QtGui>
#include <QOpenGLWidget>

#include "Entities/AbstractHuman.h"

class WidgetGL : public QOpenGLWidget
{
public:
    WidgetGL(QWidget *parent = 0);

    man::Point3F rotation;
    man::Color colorAxis;
    float scale = 1.0f;
    QPoint mousePos; // переменная для запоминания позиции нажатия мышки

    man::AbstractHuman* humanAbs = nullptr;

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
