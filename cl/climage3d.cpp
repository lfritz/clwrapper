#include "climage3d.h"

#include "clcontext.h"
#include "clerrorchecking.h"
#include "glmhelper.h"

using glm::ivec3;

ClImage3D::ClImage3D() : ClImage() { }

ClImage3D::ClImage3D(Error& error, const ClContext& context,
                     const ClImageFormat& format, ivec3 ddim,
                     ClMemAccess memAccess, bool allocHostPtr)
: ClImage(), dim(ddim) {
    init(error, context, format, ddim, 0, 0, 0, memAccess, allocHostPtr);
}

ClImage3D::ClImage3D(Error& error, const ClContext& context,
                     const ClImageFormat& format, ivec3 ddim,
                     void * copyFrom, size_t rowPitch, size_t slicePitch,
                     ClMemAccess memAccess, bool allocHostPtr)
: ClImage(), dim(ddim) {
    init(error, context, format, ddim,
         copyFrom, rowPitch, slicePitch, memAccess, allocHostPtr);
}

QVector<ClImageFormat>
ClImage3D::supportedFormats(Error& error,
                            const ClContext& context,
                            ClMemAccess memAccess, bool useHostPtr,
                            bool allocHostPtr, bool copyHostPtr) {
    return ClImage::supportedFormats(error, context, CL_MEM_OBJECT_IMAGE3D,
                                     memAccess, useHostPtr, allocHostPtr,
                                     copyHostPtr);
}

void ClImage3D::init(Error& error, const ClContext& context,
                     const ClImageFormat& format, ivec3 ddim,
                     void * copyFrom, size_t rowPitch, size_t slicePitch,
                     ClMemAccess memAccess, bool allocHostPtr) {
    cl_mem_flags flags = 0;
    if (copyFrom)                 flags |= CL_MEM_COPY_HOST_PTR;
    if (memAccess == clWriteOnly) flags |= CL_MEM_WRITE_ONLY;
    if (memAccess == clReadOnly)  flags |= CL_MEM_READ_ONLY;
    if (allocHostPtr)             flags |= CL_MEM_ALLOC_HOST_PTR;
    cl_int status = CL_SUCCESS;
    size_t width  = ddim.x;
    size_t height = ddim.y;
    size_t depth  = ddim.z;
    cl_mem mem = clCreateImage3D(context.get(), flags, format.pointer(),
                                 width, height, depth, rowPitch, slicePitch,
                                 copyFrom, &status);
    if (status == CL_SUCCESS)
        set(mem);
    else
        clCheckStatus(error, status, "clCreateImage3D");
}
