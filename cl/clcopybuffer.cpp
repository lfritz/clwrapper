#include "clcopybuffer.h"

#include "clbuffer.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"

ClCopyBuffer::ClCopyBuffer(const ClBuffer& src, const ClBuffer& dst) :
ClCommand(), s(src), d(dst),
sizeBytes(src.size()), srcOffsetBytes(0), dstOffsetBytes(0) {
}

ClCopyBuffer::ClCopyBuffer(const ClBuffer& src, const ClBuffer& dst,
                           size_t srcOffset, size_t dstOffset, size_t size) :
ClCommand(), s(src), d(dst),
sizeBytes(size), srcOffsetBytes(srcOffset), dstOffsetBytes(dstOffset) {
}

ClEvent ClCopyBuffer::enqueue(Error& error, const ClCommandQueue& queue,
                              cl_uint nEvents, const cl_event * events) {
    cl_event e;
    cl_int status = clEnqueueCopyBuffer(queue.get(), s.get(), d.get(),
                                        srcOffsetBytes, dstOffsetBytes,
                                        sizeBytes, nEvents, events, &e);
    clCheckStatus(error, status, "clEnqueueCopyBuffer");
    return ClEvent(e);
}
