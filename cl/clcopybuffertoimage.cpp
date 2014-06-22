#include "clcopybuffertoimage.h"

#include <QtGlobal>

#include "clbuffer.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "climage2d.h"
#include "climage3d.h"
#include "glmhelper.h"

using glm::ivec2;
using glm::ivec3;

ClCopyBufferToImage::ClCopyBufferToImage(const ClBuffer& src,
                                         const ClImage2D& dst,
                                         size_t offset) :
s(src), d(dst),
offset(offset),
dstOrigin(0),
region(dst.width(), dst.height(), 1) { }

ClCopyBufferToImage::ClCopyBufferToImage(const ClBuffer& src,
                                         const ClImage3D& dst,
                                         size_t offset) :
s(src), d(dst),
offset(offset),
dstOrigin(0),
region(dst.dimensions()) { }

ClCopyBufferToImage::ClCopyBufferToImage(const ClBuffer& src,
                                         const ClImage2D& dst,
                                         ivec2 dor, ivec2 r, size_t offset) :
s(src), d(dst),
offset(offset),
dstOrigin(dor.x, dor.y, 0),
region(r.x, r.y, 1) { }

ClCopyBufferToImage::ClCopyBufferToImage(const ClBuffer& src,
                                         const ClImage3D& dst,
                                         ivec3 dor, ivec3 r, size_t offset) :
s(src), d(dst),
offset(offset),
dstOrigin(dor),
region(r) { }

ClEvent ClCopyBufferToImage::enqueue(Error& error, const ClCommandQueue& queue,
                                     cl_uint nEvents, const cl_event * events) {
    size_t dor[3]; toSizeTArray(dor, dstOrigin);
    size_t r[3];   toSizeTArray(r, region);
    cl_event e = 0;
    cl_int status = clEnqueueCopyBufferToImage(queue.get(), s.get(), d.get(),
                                               offset, dor, r, nEvents, events,
                                               &e);
    clCheckStatus(error, status, "clEnqueueCopyBufferToImage");
    return ClEvent(e);
}
