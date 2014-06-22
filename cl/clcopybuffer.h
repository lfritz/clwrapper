#pragma once

#include "clcommand.h"

class ClBuffer;
class ClMem;

class ClCopyBuffer : public ClCommand {
    const ClMem& s;
    const ClMem& d;
    const size_t sizeBytes;
    const size_t srcOffsetBytes;
    const size_t dstOffsetBytes;

public:
    // copy whole buffer
    ClCopyBuffer(const ClBuffer& src, const ClBuffer& dst);

    // copy part of a buffer
    ClCopyBuffer(const ClBuffer& src, const ClBuffer& dst,
                 size_t srcOffset, size_t dstOffset, size_t size);

    ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                    cl_uint nEvents, const cl_event * events);
};
