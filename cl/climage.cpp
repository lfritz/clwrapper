#include "climage.h"

#include "clcontext.h"
#include "clerrorchecking.h"
#include "climageformat.h"
#include "error.h"

ClImage::~ClImage() { }

QVector<ClImageFormat> ClImage::supportedFormats(Error& error,
                                                 const ClContext& context,
                                                 cl_mem_object_type imageType,
                                                 ClMemAccess memAccess,
                                                 bool useHostPtr,
                                                 bool allocHostPtr,
                                                 bool copyHostPtr) {
    // combine flags
    cl_mem_flags flags = 0;
    if (memAccess == clReadWrite) flags |= CL_MEM_READ_WRITE;
    if (memAccess == clWriteOnly) flags |= CL_MEM_WRITE_ONLY;
    if (memAccess == clReadOnly)  flags |= CL_MEM_READ_ONLY;
    if (useHostPtr)               flags |= CL_MEM_USE_HOST_PTR;
    if (allocHostPtr)             flags |= CL_MEM_ALLOC_HOST_PTR;
    if (copyHostPtr)              flags |= CL_MEM_COPY_HOST_PTR;

    // find out the number of formats
    cl_uint numFormats = 0;
    cl_int status =
    clGetSupportedImageFormats(context.get(), flags, imageType, 0, 0,
                               &numFormats);
    clCheckStatus(error, status, "clGetSupportedImageFormats");
    if (error) return QVector<ClImageFormat>();

    // get the list of formats
    QVector<cl_image_format> structs(numFormats);
    status =
    clGetSupportedImageFormats(context.get(), flags, imageType, numFormats,
                               structs.data(), 0);
    clCheckStatus(error, status, "clGetSupportedImageFormats");
    if (error) return QVector<ClImageFormat>();

    // create ClImageFormat objects
    QVector<ClImageFormat> objects(numFormats);
    for (int i = 0; i < (int)numFormats; ++i)
        objects[i] = ClImageFormat(structs[i]);

    return objects;
}

ClImageFormat ClImage::getFormat(Error& error) const {
    cl_image_format value;
    getImageInfo(error, CL_IMAGE_FORMAT, value);
    return ClImageFormat(value);
}
size_t ClImage::getElementSize(Error& error) const {
    size_t value;
    getImageInfo(error, CL_IMAGE_ELEMENT_SIZE, value);
    return value;
}
size_t ClImage::getRowPitch(Error& error) const {
    size_t value;
    getImageInfo(error, CL_IMAGE_ROW_PITCH, value);
    return value;
}
size_t ClImage::getSlicePitch(Error& error) const {
    size_t value;
    getImageInfo(error, CL_IMAGE_SLICE_PITCH, value);
    return value;
}

template <typename T>
void ClImage::getImageInfo(Error& error,
                           cl_image_info paramName,
                           T& value) const {
    cl_int status = clGetImageInfo(get(), paramName, sizeof(T), &value, 0);
    clCheckStatus(error, status, "clGetImageInfo");
}
