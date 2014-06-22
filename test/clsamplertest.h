#pragma once

// Unit tests for class ClSampler.

#include <error.h>

#include "needsclcontext.h"

class ClSamplerTest : public NeedsClContext {
protected:
    Error error;
    ClSamplerTest();
    virtual ~ClSamplerTest();
};
