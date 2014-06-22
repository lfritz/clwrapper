#pragma once

#include "clcommand.h"
#include "clndrange.h"

class ClKernel;

class ClNDRangeKernel : public ClCommand {
    const ClKernel& kernel;
    const ClNDRange global;
    const ClNDRange * local;

public:
    ClNDRangeKernel(const ClKernel& k,
                    const ClNDRange globalNDRange,
                    const ClNDRange * localNDRange=0);

    ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                    cl_uint nEvents, const cl_event * events);
};
