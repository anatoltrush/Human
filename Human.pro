TARGET = Human
TEMPLATE = app
CONFIG +=  c++14
QT     +=  core gui widgets

SOURCES += \
        AbstractBone.cpp \
        AbstractHuman.cpp \
        AbstractSkeleton.cpp \
        Config.cpp \
        CyberBone.cpp \
        CyberSkeleton.cpp \
        Cyborg.cpp \
        Human.cpp \
        HumanBone.cpp \
        HumanSkeleton.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    AbstractBone.h \
    AbstractHuman.h \
    AbstractSkeleton.h \
    Config.h \
    ConfigDefines.h \
    CyberBone.h \
    CyberSkeleton.h \
    Cyborg.h \
    Defines.h \
    Human.h \
    HumanBone.h \
    HumanSkeleton.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
