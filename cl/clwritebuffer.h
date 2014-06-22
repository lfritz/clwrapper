#pragma once

#include "clblockingcommand.h"

class ClBuffer;
class ClMem;

class ClWriteBuffer : public ClBlockingCommand {
    const ClMem& mem;
    const void * ptr;
    const size_t sizeBytes;
    const size_t offsetBytes;

public:
    // write to whole buffer
    ClWriteBuffer(const ClBuffer& b, const void * p);

    // write to part of a buffer
    ClWriteBuffer(const ClBuffer& b, const void * p,
                  size_t offset, size_t size);

    ClEvent enqueueBlocking(Error& error, const ClCommandQueue& queue,
                            cl_uint nEvents, const cl_event * events,
                            bool blocking);
};
