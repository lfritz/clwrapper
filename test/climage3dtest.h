#pragma once

// Unit tests for class ClImage3D.

#include <QVector>
#include <climageformat.h>
#include <error.h>
#include <glm/glm.hpp>

#include "needsclcommandqueue.h"
#include "needsclcontext.h"

class ClImage3DTestStatic : public NeedsClContext {
protected:
    Error error;
    ClImage3DTestStatic();
    virtual ~ClImage3DTestStatic();
};

class ClImage3DTest : public NeedsClCommandQueue {
protected:
    Error error;

    ClImageFormat format;
    glm::ivec3 dim;
    size_t bufferSize;
    size_t vectorSize;
    QVector<qint32> input;
    QVector<qint32> output;

    ClImage3DTest();
    virtual ~ClImage3DTest();
};
