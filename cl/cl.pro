TARGET = cl
TEMPLATE = lib
CONFIG += staticlib

equals(QT_MAJOR_VERSION, 5) {
    CONFIG += c++11
} else {
    *-clang | *-g++ {
        QMAKE_CXXFLAGS += -std=gnu++98
    }
}

INCLUDEPATH += ../../glm

SOURCES = clblockingcommand.cpp clbuffer.cpp clcommand.cpp clcommandqueue.cpp clcontext.cpp clcopybuffer.cpp clcopybuffertoimage.cpp clcopyimage.cpp clcopyimagetobuffer.cpp cldevice.cpp clerrorchecking.cpp clevent.cpp cleventlist.cpp clew.cpp climage.cpp climage2d.cpp climage3d.cpp climageformat.cpp clkernel.cpp cllibrary.cpp clmapbuffer.cpp clmapimage.cpp clmem.cpp clndrange.cpp clndrangekernel.cpp clplatform.cpp clprogram.cpp clreadbuffer.cpp clreadimage.cpp clsampler.cpp cltask.cpp cltype.cpp clunmapbuffer.cpp clunmapimage.cpp clwritebuffer.cpp clwriteimage.cpp

HEADERS = clblockingcommand.h clbool.h clbuffer.h clcommand.h clcommandqueue.h clcontext.h clcopybuffer.h clcopybuffertoimage.h clcopyimage.h clcopyimagetobuffer.h cldevice.h clerrorchecking.h clevent.h cleventlist.h clew.h climage.h climage2d.h climage3d.h climageformat.h clkernel.h cllibrary.h clmapbuffer.h clmapimage.h clmem.h clmemaccess.h clndrange.h clndrangekernel.h clplatform.h clprogram.h clreadbuffer.h clreadimage.h clsampler.h cltask.h cltype.h clunmapbuffer.h clunmapimage.h clwritebuffer.h clwriteimage.h error.h glmhelper.h
