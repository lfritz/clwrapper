#include "clmapbuffer.h"

#include "clbool.h"
#include "clbuffer.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"

ClMapBuffer::ClMapBuffer(const ClBuffer& b, cl_map_flags flags) :
ClBlockingCommand(),
mem(b), mapFlags(flags),
sizeBytes(b.size()), offsetBytes(0) { }

ClMapBuffer::ClMapBuffer(const ClBuffer& b, cl_map_flags flags,
                         size_t offset, size_t size) :
ClBlockingCommand(),
mem(b), mapFlags(flags),
sizeBytes(size), offsetBytes(offset) { }

ClEvent ClMapBuffer::enqueueBlocking(Error& error, const ClCommandQueue& queue,
                                     cl_uint nEvents, const cl_event * events,
                                     bool blocking) {
    cl_event e = 0;
    cl_int status = CL_SUCCESS;
    ptr = clEnqueueMapBuffer(queue.get(), mem.get(), clBool(blocking),
                             mapFlags, offsetBytes, sizeBytes,
                             nEvents, events, &e, &status);
    clCheckStatus(error, status, "clEnqueueMapBuffer");
    return ClEvent(e);
}
