TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

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
