#pragma once

#include <glm/glm.hpp>

#include "clblockingcommand.h"

class ClImage2D;
class ClImage3D;
class ClMem;

// Command to read from a 2D or 3D image object to host memory.
class ClReadImage : public ClBlockingCommand {
    const ClMem& mem;
    const glm::ivec3 imageOrigin;
    const glm::ivec3 imageRegion;
    const size_t rp;
    const size_t sp;
    void * ptr;

public:
    // read whole 2D image
    ClReadImage(const ClImage2D& im, void * pptr, size_t rowPitch=0);

    // read part of 2D image
    ClReadImage(const ClImage2D& im, void * pptr,
                glm::ivec2 origin, glm::ivec2 region,
                size_t rowPitch=0);

    // read whole 3D image
    ClReadImage(const ClImage3D& im, void * pptr,
                size_t rowPitch=0, size_t slicePitch=0);

    // read part of 3D image
    ClReadImage(const ClImage3D& im, void * pptr,
                glm::ivec3 origin, glm::ivec3 region,
                size_t rowPitch=0, size_t slicePitch=0);

    ClEvent enqueueBlocking(Error& error, const ClCommandQueue& queue,
                            cl_uint nEvents, const cl_event * events,
                            bool blocking);
};
