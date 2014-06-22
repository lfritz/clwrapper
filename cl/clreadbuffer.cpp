#include "clreadbuffer.h"

#include "clbool.h"
#include "clbuffer.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"

ClReadBuffer::ClReadBuffer(const ClBuffer& b, void * p) :
ClBlockingCommand(),
mem(b), ptr(p), sizeBytes(b.size()), offsetBytes(0) { }

ClReadBuffer::ClReadBuffer(const ClBuffer& b, void * p,
                           size_t offset, size_t size) :
ClBlockingCommand(),
mem(b), ptr(p), sizeBytes(size), offsetBytes(offset) { }

ClEvent ClReadBuffer::enqueueBlocking(Error& error, const ClCommandQueue& queue,
                                      cl_uint nEvents, const cl_event * events,
                                      bool blocking) {
    cl_event e = 0;
    cl_int status = clEnqueueReadBuffer(queue.get(), mem.get(), clBool(blocking),
                                        offsetBytes, sizeBytes, ptr, nEvents,
                                        events, &e);
    clCheckStatus(error, status, "clEnqueueReadBuffer");
    return ClEvent(e);
}
