#pragma once

#include "clew.h"

class ClContext;
class Error;

class ClSampler {
    bool isValid;
    cl_sampler s;

public:
    ClSampler();
    ClSampler(Error& error,
              const ClContext& context, bool normalizedCoords,
              cl_addressing_mode addressingMode, cl_filter_mode filterMode);

    // move and copy constructors
    ClSampler(ClSampler&& rhs);
    ClSampler(const ClSampler& rhs);

    // move and copy assignment
    ClSampler& operator=(ClSampler&& rhs);
    ClSampler& operator=(const ClSampler& rhs);

    ~ClSampler();

    cl_sampler get() const { return s; }

    // missing: get context
    cl_addressing_mode getAddressingMode(Error& error) const;
    cl_filter_mode getFilterMode(Error& error) const;
    bool getNormalizedCoords(Error& error) const;

private:
    template <typename T>
    void getInfo(Error& error, cl_sampler_info paramName, T& value) const;

    void retain();
    void release();
};
