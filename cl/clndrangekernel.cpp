#include "clndrangekernel.h"

#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "clkernel.h"

ClNDRangeKernel::ClNDRangeKernel(const ClKernel& k,
                                 const ClNDRange globalNDRange,
                                 const ClNDRange * localNDRange)
: ClCommand(), kernel(k), global(globalNDRange), local(localNDRange) { }

ClEvent ClNDRangeKernel::enqueue(Error& error, const ClCommandQueue& queue,
                                 cl_uint nEvents, const cl_event * events) {
    cl_event e = 0;
    cl_int status = clEnqueueNDRangeKernel(queue.get(), kernel.get(),
                                           global.dim, 0, global.array(),
                                           local ? local->array() : 0,
                                           nEvents, events, &e);
    clCheckStatus(error, status, "clEnqueueNDRangeKernel");
    return ClEvent(e);
}
