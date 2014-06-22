#pragma once

// Unit tests for ClCommandQueue.

#include <error.h>

#include "needsclcommandqueue.h"

class ClCommandQueueTest : public NeedsClCommandQueue {
protected:
    Error error;
    ClCommandQueueTest();
    virtual ~ClCommandQueueTest();
};
