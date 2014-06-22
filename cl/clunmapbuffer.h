#pragma once

#include "clcommand.h"

class ClBuffer;
class ClMapBuffer;
class ClMem;

class ClUnmapBuffer : public ClCommand {
    const ClMem& mem;
    void * ptr;

public:
    ClUnmapBuffer(const ClBuffer& b, void * mappedPointer);
    ClUnmapBuffer(const ClMapBuffer& mapBuffer);

    ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                    cl_uint nEvents, const cl_event * events);
};
