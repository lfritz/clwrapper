#pragma once

#include "needscldevice.h"

class ClContext;

// Superclass for test fixtures that need a ClContext object.
class NeedsClContext : public NeedsClDevice {
protected:
    ClContext * c;
    NeedsClContext();
    virtual ~NeedsClContext();
    virtual void SetUp();
};
