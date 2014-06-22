#pragma once

#include "needsclplatform.h"

class ClDevice;

// Superclass for test fixtures that need a ClDevice object.
class NeedsClDevice : public NeedsClPlatform {
protected:
    ClDevice * d;
    NeedsClDevice();
    virtual ~NeedsClDevice();
};
