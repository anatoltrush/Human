TARGET  = Human
TEMPLATE = app
CONFIG  +=  c++14
QT      +=  core gui widgets network

win32: {
QT      += openglwidgets
LIBS    += -lglu32 -lopengl32
}

unix:{

}

SOURCES += \
        Algorithms/CyberReArranger.cpp \
        Algorithms/MediaPipeReArranger.cpp \
        Algorithms/OpenPoseReArranger.cpp \
        Algorithms/StlHandler.cpp \
        Auxiliary/Additional.cpp \
        Auxiliary/ExtraMath.cpp \
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
    Algorithms/AbstractReArranger.h \
    Algorithms/CyberReArranger.h \
    Algorithms/MediaPipeReArranger.h \
    Algorithms/OpenPoseReArranger.h \
    Algorithms/StlHandler.h \
    Auxiliary/Additional.h \
    Auxiliary/ExtraMath.h \
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
    Entities/PersonalInfo.h \
    Entities/Primitives.h \
    Interfaces/IOpenGL.h \
    Interfaces/IProperty.h \
    WidgetGL.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
