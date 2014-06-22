#pragma once

#include <glm/glm.hpp>

#include "clcommand.h"

class ClBuffer;
class ClImage2D;
class ClImage3D;
class ClMem;

// Command to copy from a buffer object to a 2D or 3D image object.
class ClCopyBufferToImage : public ClCommand {
    const ClMem& s;
    const ClMem& d;
    const size_t offset;
    const glm::ivec3 dstOrigin;
    const glm::ivec3 region;

public:
    // Destination is the whole image.
    ClCopyBufferToImage(const ClBuffer& src, const ClImage2D& dst,
                        size_t offset=0);
    ClCopyBufferToImage(const ClBuffer& src, const ClImage3D& dst,
                        size_t offset=0);

    // Destination is the part of the image starting at dor ("destination
    // origin") of size r ("region").
    ClCopyBufferToImage(const ClBuffer& src, const ClImage2D& dst,
                        glm::ivec2 dor, glm::ivec2 r, size_t offset=0);
    ClCopyBufferToImage(const ClBuffer& src, const ClImage3D& dst,
                        glm::ivec3 dor, glm::ivec3 r, size_t offset=0);

    ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                    cl_uint nEvents, const cl_event * events);
};
