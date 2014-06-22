#pragma once

#include <glm/glm.hpp>

#include "clcommand.h"

class ClBuffer;
class ClImage2D;
class ClImage3D;
class ClMem;

// Command to copy from a 2D or 3D image object to a buffer object.
class ClCopyImageToBuffer : public ClCommand {
    const ClMem& s;
    const ClMem& d;
    const glm::ivec3 srcOrigin;
    const glm::ivec3 region;
    const size_t offset;

public:
    // Copy whole image.
    ClCopyImageToBuffer(const ClImage2D& src, const ClBuffer& dst,
                        size_t dstOffset=0);
    ClCopyImageToBuffer(const ClImage3D& src, const ClBuffer& dst,
                        size_t dstOffset=0);

    // Copy part of an image.
    ClCopyImageToBuffer(const ClImage2D& src, const ClBuffer& dst,
                        glm::ivec2 sor, glm::ivec2 r, size_t dstOffset=0);
    ClCopyImageToBuffer(const ClImage3D& src, const ClBuffer& dst,
                        glm::ivec3 sor, glm::ivec3 r, size_t dstOffset=0);

    ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                    cl_uint nEvents, const cl_event * events);
};
