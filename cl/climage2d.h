#pragma once

#include <glm/glm.hpp>

#include "clmemaccess.h"
#include "climage.h"

class ClContext;
class Error;

// 2D image object.
class ClImage2D : public ClImage {
    const glm::ivec2 dim;

public:
    ClImage2D();

    // Create 2D image object.
    ClImage2D(Error& error, const ClContext& context,
              const ClImageFormat& format, glm::ivec2 ddim,
              ClMemAccess memAccess=clReadWrite, bool allocHostPtr=false);

    // Create 2D image object and initialize it with the data in 'copyFrom'.
    ClImage2D(Error& error, const ClContext& context,
              const ClImageFormat& format, glm::ivec2 ddim,
              void * copyFrom, size_t rowPitch=0,
              ClMemAccess memAccess=clReadWrite, bool allocHostPtr=false);

    glm::ivec2 dimensions() const { return dim; }
    int width()  const { return dim.x; }
    int height() const { return dim.y; }

    static QVector<ClImageFormat>
    supportedFormats(Error& error,
                     const ClContext& context,
                     ClMemAccess memAccess=clReadWrite, bool useHostPtr=false,
                     bool allocHostPtr=false, bool copyHostPtr=false);

private:
    void init(Error& error, const ClContext& context,
              const ClImageFormat& format, glm::ivec2 ddim,
              void * copyFrom, size_t rowPitch,
              ClMemAccess memAccess, bool allocHostPtr);
};
