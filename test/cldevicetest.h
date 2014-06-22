#pragma once

// Unit tests for class ClDevice.

#include <error.h>

#include "needscldevice.h"
#include "needsclplatform.h"

class ClDeviceTestStatic : public NeedsClPlatform {
protected:
    Error error;
    ClDeviceTestStatic();
    virtual ~ClDeviceTestStatic();
};

class ClDeviceTest : public NeedsClDevice {
protected:
    Error error;
    ClDeviceTest();
    virtual ~ClDeviceTest();
};
