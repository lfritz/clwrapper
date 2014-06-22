TARGET = cl-info
TEMPLATE = app

equals(QT_MAJOR_VERSION, 5) {
    CONFIG += c++11
} else {
    *-clang | *-g++ {
        QMAKE_CXXFLAGS += -std=c++11
    }
}

INCLUDEPATH += ../../glm

INCLUDEPATH += ../cl
!windows:LIBS += -L../cl -lcl
windows:LIBS += ../cl/release/cl.lib

# link with 'dl' library (for dlopen/dlclose/dlsym)
unix:!macx:LIBS += -ldl

SOURCES = main.cpp
