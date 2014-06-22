#include "clcopyimage.h"

#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "climage2d.h"
#include "climage3d.h"
#include "glmhelper.h"

using glm::ivec2;
using glm::ivec3;

ClCopyImage::ClCopyImage(const ClImage2D& src, const ClImage2D& dst) :
s(src), d(dst),
srcOrigin(0),
dstOrigin(0),
region(src.width(), src.height(), 1) { }

ClCopyImage::ClCopyImage(const ClImage3D& src, const ClImage3D& dst) :
s(src), d(dst),
srcOrigin(0),
dstOrigin(0),
region(src.dimensions()) { }

ClCopyImage::ClCopyImage(const ClImage2D& src, const ClImage2D& dst,
                         ivec2 sor, ivec2 dor, ivec2 r) :
s(src), d(dst),
srcOrigin(sor.x, sor.y, 0),
dstOrigin(dor.x, dor.y, 0),
region(r.x, r.y, 1) { }

ClCopyImage::ClCopyImage(const ClImage2D& src, const ClImage3D& dst,
                         ivec2 sor, ivec3 dor, ivec2 r) :
s(src), d(dst),
srcOrigin(sor.x, sor.y, 0),
dstOrigin(dor),
region(r.x, r.y, 1) { }

ClCopyImage::ClCopyImage(const ClImage3D& src, const ClImage2D& dst,
                         ivec3 sor, ivec2 dor, ivec2 r) :
s(src), d(dst),
srcOrigin(sor),
dstOrigin(dor.x, dor.y, 0),
region(r.x, r.y, 1) { }

ClCopyImage::ClCopyImage(const ClImage3D& src, const ClImage3D& dst,
                         ivec3 sor, ivec3 dor, ivec3 r) :
s(src), d(dst),
srcOrigin(sor), dstOrigin(dor), region(r) { }

ClEvent ClCopyImage::enqueue(Error& error, const ClCommandQueue& queue,
                             cl_uint nEvents, const cl_event * events) {
    size_t sor[3]; toSizeTArray(sor, srcOrigin);
    size_t dor[3]; toSizeTArray(dor, dstOrigin);
    size_t r[3];   toSizeTArray(r, region);
    cl_event e = 0;
    cl_int status = clEnqueueCopyImage(queue.get(), s.get(), d.get(),
                                       sor, dor, r, nEvents, events, &e);
    clCheckStatus(error, status, "clEnqueueCopyImage");
    return ClEvent(e);
}
