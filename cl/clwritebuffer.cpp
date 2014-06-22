#include "clwritebuffer.h"

#include "clbool.h"
#include "clbuffer.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"

ClWriteBuffer::ClWriteBuffer(const ClBuffer& b, const void * p) :
ClBlockingCommand(),
mem(b), ptr(p), sizeBytes(b.size()), offsetBytes(0) { }

ClWriteBuffer::ClWriteBuffer(const ClBuffer& b, const void * p,
                             size_t offset, size_t size) :
ClBlockingCommand(),
mem(b), ptr(p), sizeBytes(size), offsetBytes(offset) { }

ClEvent ClWriteBuffer::enqueueBlocking(Error& error,
                                       const ClCommandQueue& queue,
                                       cl_uint nEvents,
                                       const cl_event * events,
                                       bool blocking) {
    cl_event e = 0;
    cl_int status = clEnqueueWriteBuffer(queue.get(), mem.get(),
                                         clBool(blocking),
                                         offsetBytes, sizeBytes, ptr,
                                         nEvents, events, &e);
    clCheckStatus(error, status, "clEnqueueWriteBuffer");
    return ClEvent(e);
}
