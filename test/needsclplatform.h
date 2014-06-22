#pragma once

#include <gtest/gtest.h>

class ClPlatform;

// Superclass for test fixtures that need a ClPlatform object.
class NeedsClPlatform : public testing::Test {
protected:
    ClPlatform * p;
    NeedsClPlatform();
    virtual ~NeedsClPlatform();
};
