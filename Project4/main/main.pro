TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -llapack -lblas -larmadillo

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
LIBS += -fopenmp

SOURCES += \
        ising.cpp \
        main.cpp

HEADERS += \
    ising.h

DISTFILES += \
    plot.py

