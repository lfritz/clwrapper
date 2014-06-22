#pragma once

#include "clmem.h"
#include "clmemaccess.h"

class ClContext;
class Error;

// Wrapper class for OpenCL buffer objects.
class ClBuffer : public ClMem {
    size_t sizeBytes;

public:
    ClBuffer();

    // Create buffer object.
    ClBuffer(Error& error, const ClContext& context, size_t sz,
             ClMemAccess memAccess=clReadWrite, bool allocHostPtr=false);

    // Create buffer object and initialize it with the data in 'copyFrom'.
    ClBuffer(Error& error, const ClContext& context, size_t sz,
             void * copyFrom,
             ClMemAccess memAccess=clReadWrite, bool allocHostPtr=false);

    // missing: create buffer with CL_MEM_USE_HOST_PTR

    size_t size() const { return sizeBytes; }

private:
    void init(Error& error, const ClContext& context, size_t sz,
              void * copyFrom, ClMemAccess memAccess, bool allocHostPtr);
};
