#pragma once

// Unit tests for class ClPlatform.

#include <error.h>

#include "needsclplatform.h"

class ClPlatformTest : public NeedsClPlatform {
protected:
    Error error;
    ClPlatformTest();
    virtual ~ClPlatformTest();
};
