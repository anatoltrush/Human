#include "WidgetGL.h"

WidgetGL::WidgetGL(QWidget *parent):QOpenGLWidget(parent)
{
    colorAxis.x = 1.0f;
    colorAxis.y = 0.0f;
    colorAxis.z = 1.0f;
}

void WidgetGL::drawAxis()
{
    float axisLegth = 1000.0f;
    glLineWidth(2.0f); // устанавливаем ширину линии

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(-axisLegth, 0, 0);
    glVertex3f(axisLegth, 0, 0);

    glColor3f(1, 1, 0);
    glVertex3f(0, -axisLegth, 0);
    glVertex3f(0, axisLegth, 0);

    glColor3f(0, 1, 1);
    glVertex3f(0, 0, -axisLegth);
    glVertex3f(0, 0, axisLegth);
    glEnd();
}

void WidgetGL::initializeGL()
{
    glClearColor(0.5f, 0.55f, 0.6f, 0.3f); // заполняем экран цветом
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    //glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // фигуры будут закрашены с обеих сторон
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // видны только ребра
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
    glRotatef(rotation.z, 0.0, 0.0, 1.0);

    glScalef(scale, scale, scale);

    drawAxis();

    // DRAW
    if(human){
        for(const auto &bone : human->skeleton->bones)
            bone->drawObjectGL();
    }
    if(cyborg){
        for(const auto &bone : cyborg->skeleton->bones)
            bone->drawObjectGL();
    }
}

void WidgetGL::mousePressEvent(QMouseEvent *pe)
{
    mousePos = pe->pos();
}

void WidgetGL::mouseMoveEvent(QMouseEvent *pe)
{
    rotation.x -= (180/scale*(GLfloat)(pe->position().y() - mousePos.y())/height()) * scale; // вычисляем углы поворота
    rotation.z -= (180/scale*(GLfloat)(pe->position().x() - mousePos.x())/width()) * scale;
    mousePos = pe->pos();

    update();
}

void WidgetGL::mouseReleaseEvent(QMouseEvent *pe)
{

}

void WidgetGL::wheelEvent(QWheelEvent *pe)
{
    float wheelScale = 1.1f;
    if ((pe->angleDelta().y()) > 0) scale *= wheelScale;
    else scale /= wheelScale;

    update();
}
