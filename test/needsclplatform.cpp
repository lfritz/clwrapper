#include "needsclplatform.h"

#include "env.h"

NeedsClPlatform::NeedsClPlatform() :
    Test(), p(0) {
    p = env->platform();
}

NeedsClPlatform::~NeedsClPlatform() { }
