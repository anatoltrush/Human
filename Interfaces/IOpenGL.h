#ifndef IOPENGL_H
#define IOPENGL_H

#include <QColor>

namespace man{

const QColor colDeepPink(255, 20, 147);
const QColor colLightGreen(144, 238, 144);
const QColor colDeepSkyBlue(0, 191, 255);

const QColor colFuchsia(255, 0, 255);
const QColor colGoldenRod(218, 165, 32);
const QColor colTomato(255, 99, 71);

const QColor colOrange(218, 165, 32);
const QColor colDarkOrange(255, 140, 0);

class IOpenGL
{
public:
    IOpenGL() = default;
    virtual ~IOpenGL() = default;

    QColor color      = Qt::black;
    QColor colorCut   = Qt::gray;
    QColor colorHull  = Qt::lightGray;

    virtual void drawObjectGL() const = 0;

};

}

#endif // IOPENGL_H
