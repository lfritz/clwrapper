#pragma once

#include <glm/glm.hpp>

#include "clblockingcommand.h"

class ClImage2D;
class ClImage3D;
class ClMem;

class ClMapImage : public ClBlockingCommand {
    const ClMem& mem;
    const cl_map_flags mapFlags;
    const glm::ivec3 imageOrigin;
    const glm::ivec3 imageRegion;
    size_t rowPitch;
    size_t slicePitch;
    void * ptr;

public:
    // Map whole image.
    ClMapImage(const ClImage2D& i, cl_map_flags flags);
    ClMapImage(const ClImage3D& i, cl_map_flags flags);

    // Map part of an image.
    ClMapImage(const ClImage2D& i, cl_map_flags flags,
               glm::ivec2 origin, glm::ivec2 region);
    ClMapImage(const ClImage3D& i, cl_map_flags flags,
               glm::ivec3 origin, glm::ivec3 region);

    ClEvent enqueueBlocking(Error& error, const ClCommandQueue& queue,
                            cl_uint nEvents, const cl_event * events,
                            bool blocking);

    const ClMem& memObject() const { return mem; }
    void * pointer() const { return ptr; }
    size_t imageRowPitch() const { return rowPitch; }
    size_t imageSlicePitch() const { return slicePitch; }
};
