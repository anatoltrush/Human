TARGET  = Human
TEMPLATE = app
CONFIG  +=  c++14
QT      +=  core gui widgets

win32: {
QT      += openglwidgets
LIBS    += -lglu32 -lopengl32
}

unix:{

}

SOURCES += \
        Algorithms/ExtraMath.cpp \
        Algorithms/StlHandler.cpp \
        Config/Config.cpp \
        Entities/AbstractBone.cpp \
        Entities/AbstractHuman.cpp \
        Entities/AbstractSkeleton.cpp \
        Entities/CutSurface.cpp \
        Entities/CyberBone.cpp \
        Entities/CyberSkeleton.cpp \
        Entities/Cyborg.cpp \
        Entities/Human.cpp \
        Entities/HumanBone.cpp \
        Entities/HumanSkeleton.cpp \
        Entities/PersonalInfo.cpp \
        WidgetGL.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    Algorithms/ExtraMath.h \
    Algorithms/StlHandler.h \
    Config/Config.h \
    Config/ConfigDefines.h \
    Config/Defines.h \
    Entities/AbstractBone.h \
    Entities/AbstractHuman.h \
    Entities/AbstractSkeleton.h \
    Entities/CutSurface.h \
    Entities/CyberBone.h \
    Entities/CyberSkeleton.h \
    Entities/Cyborg.h \
    Entities/Human.h \
    Entities/HumanBone.h \
    Entities/HumanSkeleton.h \
    Entities/IOpenGL.h \
    Entities/PersonalInfo.h \
    Entities/Primitives.h \
    WidgetGL.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
