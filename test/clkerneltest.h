#pragma once

// Unit tests for class ClKernel.

#include <QVector>
#include <clprogram.h>
#include <error.h>

#include "needsclcommandqueue.h"

class ClKernelTest : public NeedsClCommandQueue {
protected:
    Error error;
    ClProgram program;

    ClKernelTest();
    virtual ~ClKernelTest();
    virtual void SetUp();
};

class ClKernelTestRun : public NeedsClCommandQueue {
protected:
    Error error;
    ClProgram program;
    const size_t vectorSize;
    QVector<int> vector;
    QVector<int> vectorPlus1;

    ClKernelTestRun();
    ~ClKernelTestRun();
    virtual void SetUp();
};
