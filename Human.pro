TEMPLATE = app
CONFIG +=  c++17
QT     +=  core gui

SOURCES += \
        AbstractBone.cpp \
        AbstractHuman.cpp \
        AbstractSkeleton.cpp \
        CyberBone.cpp \
        CyberSkeleton.cpp \
        Cyborg.cpp \
        Human.cpp \
        HumanBone.cpp \
        HumanSkeleton.cpp \
        main.cpp

HEADERS += \
    AbstractBone.h \
    AbstractHuman.h \
    AbstractSkeleton.h \
    CyberBone.h \
    CyberSkeleton.h \
    Cyborg.h \
    Defines.h \
    Human.h \
    HumanBone.h \
    HumanSkeleton.h
