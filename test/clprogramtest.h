#pragma once

// Unit tests for class ClProgram.

#include <error.h>

#include "needsclcontext.h"

class ClProgramTest : public NeedsClContext {
protected:
    Error error;
    ClProgramTest();
    virtual ~ClProgramTest();
};
