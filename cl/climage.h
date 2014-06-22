#pragma once

#include <QVector>

#include "climageformat.h"
#include "clmem.h"
#include "clmemaccess.h"

class ClContext;
class Error;

// Abstract superclass for 2D and 3D image objects.
class ClImage : public ClMem {
public:
    ClImage() : ClMem() { }
    virtual ~ClImage() = 0;

    ClImageFormat getFormat(Error& error) const;
    size_t getElementSize(Error& error) const;
    size_t getRowPitch(Error& error) const;
    size_t getSlicePitch(Error& error) const;

protected:
    static QVector<ClImageFormat>
    supportedFormats(Error& error,
                     const ClContext& context,
                     cl_mem_object_type imageType,
                     ClMemAccess memAccess,
                     bool useHostPtr,
                     bool allocHostPtr,
                     bool copyHostPtr);

    template <typename T>
    void getImageInfo(Error& error, cl_image_info paramName, T& value) const;
};
