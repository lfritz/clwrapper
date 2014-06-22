#pragma once

#include "clblockingcommand.h"

class ClBuffer;
class ClMem;

class ClMapBuffer : public ClBlockingCommand {
    const ClMem& mem;
    const cl_map_flags mapFlags;
    const size_t sizeBytes;
    const size_t offsetBytes;
    void * ptr;

public:
    // map whole buffer
    ClMapBuffer(const ClBuffer& b, cl_map_flags flags);

    // map part of a buffer
    ClMapBuffer(const ClBuffer& b, cl_map_flags flags,
                size_t offset, size_t size);

    ClEvent enqueueBlocking(Error& error, const ClCommandQueue& queue,
                            cl_uint nEvents, const cl_event * events,
                            bool blocking);

    const ClMem& memObject() const { return mem; }
    void * pointer() const { return ptr; }
};
