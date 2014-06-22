#pragma once

#include "clblockingcommand.h"

class ClBuffer;
class ClMem;

class ClReadBuffer : public ClBlockingCommand {
    const ClMem& mem;
    void * ptr;
    const size_t sizeBytes;
    const size_t offsetBytes;

public:
    // read whole buffer
    ClReadBuffer(const ClBuffer& b, void * p);

    // read from part of a buffer
    ClReadBuffer(const ClBuffer& b, void * p, size_t offset, size_t size);

    ClEvent enqueueBlocking(Error& error, const ClCommandQueue& queue,
                            cl_uint nEvents, const cl_event * events,
                            bool blocking);
};
