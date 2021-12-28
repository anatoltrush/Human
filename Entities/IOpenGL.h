#ifndef IOPENGL_H
#define IOPENGL_H

namespace man{

class IOpenGL
{
public:
    IOpenGL() = default;
    virtual ~IOpenGL() = default;

    virtual void drawObjectGL() const = 0;
};

}

#endif // IOPENGL_H
