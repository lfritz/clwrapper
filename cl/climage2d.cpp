#include "climage2d.h"

#include "clcontext.h"
#include "clerrorchecking.h"
#include "glmhelper.h"

using glm::ivec2;

ClImage2D::ClImage2D() : ClImage() { }

ClImage2D::ClImage2D(Error& error, const ClContext& context,
                     const ClImageFormat& format, ivec2 ddim,
                     ClMemAccess memAccess, bool allocHostPtr)
: ClImage(), dim(ddim) {
    init(error, context, format, ddim, 0, 0, memAccess, allocHostPtr);
}

ClImage2D::ClImage2D(Error& error, const ClContext& context,
                     const ClImageFormat& format, ivec2 ddim,
                     void * copyFrom, size_t rowPitch,
                     ClMemAccess memAccess, bool allocHostPtr)
: ClImage(), dim(ddim) {
    init(error, context, format, ddim,
         copyFrom, rowPitch, memAccess, allocHostPtr);
}

QVector<ClImageFormat>
ClImage2D::supportedFormats(Error& error,
                            const ClContext& context,
                            ClMemAccess memAccess, bool useHostPtr,
                            bool allocHostPtr, bool copyHostPtr) {
    return ClImage::supportedFormats(error, context, CL_MEM_OBJECT_IMAGE2D,
                                     memAccess, useHostPtr, allocHostPtr,
                                     copyHostPtr);
}

void ClImage2D::init(Error& error, const ClContext& context,
                     const ClImageFormat& format, ivec2 ddim,
                     void * copyFrom, size_t rowPitch,
                     ClMemAccess memAccess, bool allocHostPtr) {
    cl_mem_flags flags = 0;
    if (copyFrom)                 flags |= CL_MEM_COPY_HOST_PTR;
    if (memAccess == clWriteOnly) flags |= CL_MEM_WRITE_ONLY;
    if (memAccess == clReadOnly)  flags |= CL_MEM_READ_ONLY;
    if (allocHostPtr)             flags |= CL_MEM_ALLOC_HOST_PTR;
    size_t width  = ddim.x;
    size_t height = ddim.y;
    cl_int status = CL_SUCCESS;
    cl_mem mem =
    clCreateImage2D(context.get(), flags, format.pointer(),
                    width, height, rowPitch, copyFrom, &status);
    if (status == CL_SUCCESS)
        set(mem);
    else
        clCheckStatus(error, status, "clCreateImage2D");
}
