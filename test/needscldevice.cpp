#include "needscldevice.h"

#include "env.h"

NeedsClDevice::NeedsClDevice() :
    NeedsClPlatform(), d(0) {
    d = env->device();
}

NeedsClDevice::~NeedsClDevice() { }
