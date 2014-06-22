#pragma once

#include <QList>

#include "clew.h"

class ClDevice;
class ClPlatform;
class Error;

// Wrapper class for OpenCL contexts.
class ClContext {
    bool isValid;
    cl_context c;

public:
    ClContext();
    ClContext(Error& error, const ClPlatform& platform, const ClDevice& device);
    ClContext(Error& error, const ClPlatform& platform,
            const QList<ClDevice> devices);
    ClContext(Error& error, const ClPlatform& platform,
            cl_device_type deviceType);

    // missing: creating a context with a callback function

    // move and copy constructors
    ClContext(ClContext&& rhs);
    ClContext(const ClContext& rhs);

    // move and copy assignment
    ClContext& operator=(ClContext&& rhs);
    ClContext& operator=(const ClContext& rhs);

    ~ClContext();

    cl_context get() const { return c; }

    QList<ClDevice> getDevices(Error& error) const;

private:
    // helper functions for querying context info
    size_t getInfoSize(Error& error, cl_context_info paramName) const;
    void getInfoArray(Error& error, cl_context_info paramName, void * data,
                      size_t size) const;

    void retain();
    void release();
};
