#pragma once

// Unit tests for class ClBuffer.

#include <QVector>
#include <error.h>

#include "needsclcommandqueue.h"
#include "needsclcontext.h"

class ClBufferTestCreate : public NeedsClContext {
protected:
    Error error;
    ClBufferTestCreate();
    virtual ~ClBufferTestCreate();
};

class ClBufferTest : public NeedsClCommandQueue {
protected:
    Error error;

    const size_t bufferSize;
    QVector<quint8> input;
    QVector<quint8> output;

    ClBufferTest();
    virtual ~ClBufferTest();
};
