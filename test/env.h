#pragma once

#include <gtest/gtest.h>

class ClDevice;
class ClLibrary;
class ClPlatform;

// Test environment. Loads OpenCL library and provides platform and device
// objects.
class Env : public testing::Environment {
    int pid;
    int did;

    ClLibrary * l;
    ClPlatform * p;
    ClDevice * d;

public:
    Env(int platformId, int deviceId);
    ~Env();
    virtual void SetUp();
    virtual void TearDown();

    int platformId() const { return pid; }
    int deviceId() const { return did; }
    ClLibrary * library() const { return l; }
    ClPlatform * platform() const { return p; }
    ClDevice * device() const { return d; }
};

extern Env * env;
