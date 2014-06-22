#pragma once

// Unit tests for class ClEvent.

#include <error.h>

#include "needsclcommandqueue.h"

class ClEventTest : public NeedsClCommandQueue {
protected:
    Error error;
    ClEventTest();
    virtual ~ClEventTest();
};
