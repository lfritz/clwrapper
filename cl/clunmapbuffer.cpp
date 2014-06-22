#include "clunmapbuffer.h"

#include "clbuffer.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "clmapbuffer.h"

ClUnmapBuffer::ClUnmapBuffer(const ClBuffer& b, void * mappedPointer) :
mem(b), ptr(mappedPointer) { }

ClUnmapBuffer::ClUnmapBuffer(const ClMapBuffer& mapBuffer) :
mem(mapBuffer.memObject()), ptr(mapBuffer.pointer()) { }

ClEvent ClUnmapBuffer::enqueue(Error& error, const ClCommandQueue& queue,
                               cl_uint nEvents, const cl_event * events) {
    cl_event e = 0;
    cl_int status = clEnqueueUnmapMemObject(queue.get(), mem.get(), ptr,
                                            nEvents, events, &e);
    clCheckStatus(error, status, "clEnqueueUnmapMemObject");
    return ClEvent(e);
}
