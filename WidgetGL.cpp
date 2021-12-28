#include "WidgetGL.h"

WidgetGL::WidgetGL(QWidget *parent):QOpenGLWidget(parent)
{
    colorAxis.x = 1.0f;
    colorAxis.y = 0.0f;
    colorAxis.z = 1.0f;
}

void WidgetGL::drawAxis()
{
    glLineWidth(3.0f); // устанавливаем ширину линии

    glColor4f(colorAxis.x, colorAxis.y, colorAxis.z, 1.0f); // устанавливается цвет последующих линий
    // ось x
    /*glBegin(GL_LINES); // построение линии
        glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
        glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
    glEnd();
    glBegin(GL_LINES);
        // ось y
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 0.0f, -1.0f,  0.0f);

    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
        // ось z
        glVertex3f( 0.0f,  0.0f,  1.0f);
        glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();*/
    //---
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(20, 0, 0);

        glColor3f(1, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 20, 0);

        glColor3f(0, 1, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 20);
    glEnd();
}

void WidgetGL::initializeGL()
{
    glClearColor(0.3f, 0.4f, 0.5f, 0.2f); // заполняем экран цветом
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    //glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // фигуры будут закрашены с обеих сторон
}

void WidgetGL::resizeGL(int w, int h)
{

}

void WidgetGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();

    glRotatef(rotation.x, 1.0, 0.0, 0.0);
    glRotatef(rotation.y, 0.0, 1.0, 0.0);
    glRotatef(rotation.y, 0.0, 0.0, 1.0);

    glScalef(0.8, 0.8, 0.8);

    drawAxis();

    // DRAW
    /*for(const auto &row : cloud)
        for(const auto &pt : row)
            pt.drawGLtriangle(0.8);*/

    glFlush();
    makeCurrent();
}

void WidgetGL::mousePressEvent(QMouseEvent *pe)
{

}

void WidgetGL::mouseMoveEvent(QMouseEvent *pe)
{

}

void WidgetGL::mouseReleaseEvent(QMouseEvent *pe)
{

}

void WidgetGL::wheelEvent(QWheelEvent *pe)
{

}
