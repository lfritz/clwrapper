#pragma once

#include "clevent.h"

class ClCommandQueue;
class Error;

// Abstract base class for commands that can be enqueued in a OpenCL command
// queue.
class ClCommand {
public:
    virtual ~ClCommand();
    virtual ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                            cl_uint nEvents, const cl_event * events) = 0;
};
