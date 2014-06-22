#pragma once

#include <QList>

#include "clew.h"
#include "clplatform.h"

class Error;

// Class to load OpenCL library. Before using any OpenCL functionality, create
// an instance of this class and call 'clewStatus' to check that OpenCL is
// initialized properly.
class ClLibrary {
    int status;

public:
    // Load OpenCL library.
    ClLibrary();

    // CLEW status. 0 means success.
    int clewStatus() const { return status; }

    // OpenCL library file name.
    const char * filename() const;

    // Get a list of the platforms available.
    QList<ClPlatform> platforms(Error& error) const;
};
