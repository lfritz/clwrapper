#pragma once

#include "clcommand.h"

// Abstract base class for commands that can be blocking or not.
class ClBlockingCommand : public ClCommand {
public:
    virtual ~ClBlockingCommand();
    virtual ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                            cl_uint nEvents, const cl_event * events);
    virtual ClEvent enqueueBlocking(Error& error, const ClCommandQueue& queue,
                                    cl_uint nEvents, const cl_event * events,
                                    bool blocking) = 0;
};
