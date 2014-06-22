#pragma once

#include <QString>

#include "clew.h" // for cl_uint

// When using data-parallel execution with OpenCL, an NDRange is used to
// specify an index space, which determines how many work-items to execute for
// a kernel, and their identifiers. With OpenCL 1.0, an NDRange can be one-,
// two- or three-dimensional.
class ClNDRange {
    size_t values[3];

public:
    // Create a 3-dimensional index space.
    ClNDRange(size_t dim0, size_t dim1, size_t dim2);

    // Create a 2-dimensional index space.
    ClNDRange(size_t dim0, size_t dim1);

    // Create a 1-dimensional index space.
    ClNDRange(size_t dim0);

    const size_t * array() const { return values; }

    const cl_uint dim;
    const QString asString;
};
