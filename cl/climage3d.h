#pragma once

#include <glm/glm.hpp>

#include "clmemaccess.h"
#include "climage.h"

class ClContext;
class Error;

// 3D image object.
class ClImage3D : public ClImage {
    const glm::ivec3 dim;

public:
    ClImage3D();

    // Create 3D image object.
    ClImage3D(Error& error, const ClContext& context,
              const ClImageFormat& format, glm::ivec3 ddim,
              ClMemAccess memAccess=clReadWrite, bool allocHostPtr=false);

    // Create 3D image object and initialize it with the data in 'copyFrom'.
    ClImage3D(Error& error, const ClContext& context,
              const ClImageFormat& format, glm::ivec3 ddim,
              void * copyFrom, size_t rowPitch=0, size_t slicePitch=0,
              ClMemAccess memAccess=clReadWrite, bool allocHostPtr=false);

    glm::ivec3 dimensions() const { return dim; }
    int width()  const { return dim.x; }
    int height() const { return dim.y; }
    int depth()  const { return dim.z; }

    static QVector<ClImageFormat>
    supportedFormats(Error& error,
                     const ClContext& context,
                     ClMemAccess memAccess=clReadWrite, bool useHostPtr=false,
                     bool allocHostPtr=false, bool copyHostPtr=false);

private:
    void init(Error& error, const ClContext& context,
              const ClImageFormat& format, glm::ivec3 ddim,
              void * copyFrom, size_t rowPitch, size_t slicePitch,
              ClMemAccess memAccess, bool allocHostPtr);
};
