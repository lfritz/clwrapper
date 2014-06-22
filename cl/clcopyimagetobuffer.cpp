#include "clcopyimagetobuffer.h"

#include "clbuffer.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "climage2d.h"
#include "climage3d.h"
#include "glmhelper.h"

using glm::ivec2;
using glm::ivec3;

ClCopyImageToBuffer::ClCopyImageToBuffer(const ClImage2D& src,
                                         const ClBuffer& dst,
                                         size_t dstOffset) :
s(src), d(dst),
srcOrigin(0),
region(src.width(), src.height(), 1),
offset(dstOffset) { }

ClCopyImageToBuffer::ClCopyImageToBuffer(const ClImage3D& src,
                                         const ClBuffer& dst,
                                         size_t dstOffset) :
s(src), d(dst),
srcOrigin(0),
region(src.dimensions()),
offset(dstOffset) { }

ClCopyImageToBuffer::ClCopyImageToBuffer(const ClImage2D& src,
                                         const ClBuffer& dst,
                                         glm::ivec2 sor, glm::ivec2 r,
                                         size_t dstOffset) :
s(src), d(dst),
srcOrigin(sor.x, sor.y, 0),
region(r.x, r.y, 1),
offset(dstOffset) { }

ClCopyImageToBuffer::ClCopyImageToBuffer(const ClImage3D& src,
                                         const ClBuffer& dst,
                                         glm::ivec3 sor, glm::ivec3 r,
                                         size_t dstOffset) :
s(src), d(dst),
srcOrigin(sor),
region(r),
offset(dstOffset) { }

ClEvent ClCopyImageToBuffer::enqueue(Error& error, const ClCommandQueue& queue,
                                     cl_uint nEvents, const cl_event * events) {
    size_t sor[3]; toSizeTArray(sor, srcOrigin);
    size_t r[3];   toSizeTArray(r, region);
    cl_event e = 0;
    cl_int status = clEnqueueCopyImageToBuffer(queue.get(), s.get(), d.get(),
                                               sor, r, offset, nEvents, events,
                                               &e);
    clCheckStatus(error, status, "clEnqueueCopyImageToBuffer");
    return ClEvent(e);
}
