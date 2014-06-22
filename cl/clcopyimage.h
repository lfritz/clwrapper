#pragma once

#include <glm/glm.hpp>

#include "clcommand.h"

class ClImage2D;
class ClImage3D;
class ClMem;

// Command to copy from a 2D or 3D image object to a 2D or 3D image object.
class ClCopyImage : public ClCommand {
    const ClMem& s;
    const ClMem& d;
    const glm::ivec3 srcOrigin;
    const glm::ivec3 dstOrigin;
    const glm::ivec3 region;

public:
    // Copy whole image.
    ClCopyImage(const ClImage2D& src, const ClImage2D& dst);
    ClCopyImage(const ClImage3D& src, const ClImage3D& dst);

    // Copy part of an image.
    //
    // For each of these, sor defines the starting location in src ("src
    // origin"), dor defines the starting location in dst ("dst origin"), and r
    // defines the width/height/depth of the region to copy.
    ClCopyImage(const ClImage2D& src, const ClImage2D& dst,
                glm::ivec2 sor, glm::ivec2 dor, glm::ivec2 r);
    ClCopyImage(const ClImage2D& src, const ClImage3D& dst,
                glm::ivec2 sor, glm::ivec3 dor, glm::ivec2 r);
    ClCopyImage(const ClImage3D& src, const ClImage2D& dst,
                glm::ivec3 sor, glm::ivec2 dor, glm::ivec2 r);
    ClCopyImage(const ClImage3D& src, const ClImage3D& dst,
                glm::ivec3 sor, glm::ivec3 dor, glm::ivec3 r);

    ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                    cl_uint nEvents, const cl_event * events);
};
