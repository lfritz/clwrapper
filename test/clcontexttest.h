#pragma once

// Unit tests for class ClContext.

#include <error.h>

#include "needsclcontext.h"

class ClContextTest : public NeedsClContext {
protected:
    Error error;
    ClContextTest();
    virtual ~ClContextTest();
};
