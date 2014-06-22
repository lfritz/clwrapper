TARGET = cl-test
TEMPLATE = app

equals(QT_MAJOR_VERSION, 5) {
    CONFIG += c++11
} else {
    *-clang | *-g++ {
        QMAKE_CXXFLAGS += -std=c++11
    }
}

# use cl library
INCLUDEPATH += ../cl
!windows:LIBS += -L../cl -lcl
windows:LIBS += ../cl/release/cl.lib

# link with 'dl' library (for dlopen/dlclose/dlsym)
unix:!macx:LIBS += -ldl

INCLUDEPATH += ../../glm

# use googletest library
GTEST_PATH = ../../gtest-1.7.0
INCLUDEPATH += $$GTEST_PATH
INCLUDEPATH += $$GTEST_PATH/include

SOURCES += \
    $$GTEST_PATH/src/gtest-all.cc \
    clbuffertest.cpp \
    clcommandqueuetest.cpp \
    clcontexttest.cpp \
    cldevicetest.cpp \
    cleventtest.cpp \
    climage2dtest.cpp \
    climage3dtest.cpp \
    clkerneltest.cpp \
    clplatformtest.cpp \
    clprogramtest.cpp \
    clsamplertest.cpp \
    cltypetest.cpp \
    env.cpp \
    errorassert.cpp \
    main.cpp \
    needsclcommandqueue.cpp \
    needsclcontext.cpp \
    needscldevice.cpp \
    needsclplatform.cpp \

HEADERS += \
    clbuffertest.h \
    clcommandqueuetest.h \
    clcontexttest.h \
    cldevicetest.h \
    cleventtest.h \
    climage2dtest.h \
    climage3dtest.h \
    clkerneltest.h \
    clplatformtest.h \
    clprogramtest.h \
    clsamplertest.h \
    cltypetest.h \
    env.h \
    errorassert.h \
    needsclcommandqueue.h \
    needsclcontext.h \
    needscldevice.h \
    needsclplatform.h \

OTHER_FILES += \
    bad.cl \
    good.cl \
    mountainLionIssue.cl \
