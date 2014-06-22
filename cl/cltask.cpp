#include "cltask.h"

#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "clkernel.h"

ClTask::ClTask(const ClKernel& k) : ClCommand(), kernel(k) { }

ClEvent ClTask::enqueue(Error& error, const ClCommandQueue& queue,
                        cl_uint nEvents, const cl_event * events) {
    cl_event e = 0;
    cl_int status = clEnqueueTask(queue.get(), kernel.get(),
                                  nEvents, events, &e);
    clCheckStatus(error, status, "clEnqueueTask");
    return ClEvent(e);
}
