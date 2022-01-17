#ifndef IOPENGL_H
#define IOPENGL_H

#include <QColor>

namespace man{

const QColor colOrange(218, 165, 32);

class IOpenGL
{
public:
    IOpenGL() = default;
    virtual ~IOpenGL() = default;

    QColor color      = Qt::black;
    QColor colorCut   = Qt::gray;

    virtual void drawObjectGL() const = 0;

};

}

#endif // IOPENGL_H
