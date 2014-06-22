#include "clwriteimage.h"

#include "clbool.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "climage2d.h"
#include "climage3d.h"
#include "glmhelper.h"

using glm::ivec2;
using glm::ivec3;

ClWriteImage::ClWriteImage(const ClImage2D& im, const void * pptr,
                           size_t rowPitch) :
mem(im),
imageOrigin(0), imageRegion(im.width(), im.height(), 1),
rp(rowPitch), sp(0), ptr(pptr) { }

ClWriteImage::ClWriteImage(const ClImage2D& im, const void * pptr,
                           ivec2 origin, ivec2 region,
                           size_t rowPitch) :
mem(im),
imageOrigin(origin.x, origin.y, 0),
imageRegion(region.x, region.y, 1),
rp(rowPitch), sp(0), ptr(pptr) { }

ClWriteImage::ClWriteImage(const ClImage3D& im, const void * pptr,
                           size_t rowPitch, size_t slicePitch) :
mem(im),
imageOrigin(0), imageRegion(im.dimensions()),
rp(rowPitch), sp(slicePitch), ptr(pptr) { }

ClWriteImage::ClWriteImage(const ClImage3D& im, const void * pptr,
                           ivec3 origin, ivec3 region,
                           size_t rowPitch, size_t slicePitch) :
mem(im),
imageOrigin(origin), imageRegion(region),
rp(rowPitch), sp(slicePitch), ptr(pptr) { }

ClEvent ClWriteImage::enqueueBlocking(Error& error, const ClCommandQueue& queue,
                                      cl_uint nEvents, const cl_event * events,
                                      bool blocking) {
    size_t o[3]; toSizeTArray(o, imageOrigin);
    size_t r[3]; toSizeTArray(r, imageRegion);
    cl_event e = 0;
    cl_int status = clEnqueueWriteImage(queue.get(), mem.get(),
                                        clBool(blocking), o, r, rp, sp, ptr,
                                        nEvents, events, &e);
    clCheckStatus(error, status, "clEnqueueWriteImage");
    return ClEvent(e);
}
