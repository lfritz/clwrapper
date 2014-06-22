#pragma once

// Unit tests for class ClImage2D.

#include <QVector>
#include <climageformat.h>
#include <error.h>
#include <glm/glm.hpp>

#include "needsclcommandqueue.h"
#include "needsclcontext.h"

class ClImage2DTestStatic : public NeedsClContext {
protected:
    Error error;
    ClImage2DTestStatic();
    virtual ~ClImage2DTestStatic();
};

class ClImage2DTest : public NeedsClCommandQueue {
protected:
    Error error;

    ClImageFormat format;
    glm::ivec2 dim;
    size_t bufferSize;
    size_t vectorSize;
    QVector<qint32> input;
    QVector<qint32> output;

    ClImage2DTest();
    virtual ~ClImage2DTest();
};
