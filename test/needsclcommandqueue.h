#pragma once

#include "needsclcontext.h"

class ClCommandQueue;

// Superclass for test fixtures that needs a ClCommandQueue object.
class NeedsClCommandQueue : public NeedsClContext {
protected:
    ClCommandQueue * q;
    NeedsClCommandQueue();
    virtual ~NeedsClCommandQueue();
    virtual void SetUp();
};
