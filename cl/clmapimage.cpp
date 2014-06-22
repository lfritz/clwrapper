#include "clmapimage.h"

#include "clbool.h"
#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "climage2d.h"
#include "climage3d.h"
#include "glmhelper.h"

using glm::ivec2;
using glm::ivec3;

ClMapImage::ClMapImage(const ClImage2D& i, cl_map_flags flags) :
ClBlockingCommand(),
mem(i), mapFlags(flags),
imageOrigin(0),
imageRegion(i.width(), i.height(), 1) { }

ClMapImage::ClMapImage(const ClImage3D& i, cl_map_flags flags) :
ClBlockingCommand(),
mem(i), mapFlags(flags),
imageOrigin(0),
imageRegion(i.dimensions()) { }

ClMapImage::ClMapImage(const ClImage2D& i, cl_map_flags flags,
                       glm::ivec2 origin, glm::ivec2 region) :
ClBlockingCommand(),
mem(i), mapFlags(flags),
imageOrigin(origin.x, origin.y, 0),
imageRegion(region.x, region.y, 1) { }

ClMapImage::ClMapImage(const ClImage3D& i, cl_map_flags flags,
                       glm::ivec3 origin, glm::ivec3 region) :
ClBlockingCommand(),
mem(i), mapFlags(flags),
imageOrigin(origin), imageRegion(region) { }

ClEvent ClMapImage::enqueueBlocking(Error& error, const ClCommandQueue& queue,
                                    cl_uint nEvents, const cl_event * events,
                                    bool blocking) {
    size_t origin[3]; toSizeTArray(origin, imageOrigin);
    size_t region[3]; toSizeTArray(region, imageRegion);
    cl_event e = 0;
    cl_int status = CL_SUCCESS;
    ptr = clEnqueueMapImage(queue.get(), mem.get(), clBool(blocking), mapFlags,
                            origin, region, &rowPitch, &slicePitch,
                            nEvents, events, &e, &status);
    clCheckStatus(error, status, "clEnqueueMapImage");
    return ClEvent(e);
}
