#pragma once

#include "clcommand.h"

class ClKernel;

class ClTask : public ClCommand {
    const ClKernel& kernel;

public:
    ClTask(const ClKernel& k);

    ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                    cl_uint nEvents, const cl_event * events);
};
