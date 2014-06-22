#include "clsampler.h"

#include "clbool.h"
#include "clcontext.h"
#include "clerrorchecking.h"
#include "error.h"

ClSampler::ClSampler()
: isValid(false), s(0) { }

ClSampler::ClSampler(Error& error,
                     const ClContext& context,
                     bool normalizedCoords,
                     cl_addressing_mode addressingMode,
                     cl_filter_mode filterMode)
: isValid(false), s(0) {
    cl_int status = CL_SUCCESS;
    s = clCreateSampler(context.get(), clBool(normalizedCoords),
                        addressingMode, filterMode, &status);
    if (status == CL_SUCCESS)
        isValid = true;
    else
        clCheckStatus(error, status, "clCreateSampler");
}

ClSampler::ClSampler(ClSampler&& rhs)
: isValid(rhs.isValid), s(rhs.s) {
    rhs.isValid = false;
}
ClSampler::ClSampler(const ClSampler& rhs)
: isValid(rhs.isValid), s(rhs.s) {
    retain();
}

ClSampler& ClSampler::operator=(ClSampler&& rhs) {
    release();
    isValid = rhs.isValid;
    s = rhs.s;
    rhs.isValid = false;
    return *this;
}
ClSampler& ClSampler::operator=(const ClSampler& rhs) {
    release();
    isValid = rhs.isValid;
    s = rhs.s;
    retain();
    return *this;
}

ClSampler::~ClSampler() {
    release();
}

cl_addressing_mode ClSampler::getAddressingMode(Error& error) const {
    cl_addressing_mode value;
    getInfo(error, CL_SAMPLER_ADDRESSING_MODE, value);
    return value;
}

cl_filter_mode ClSampler::getFilterMode(Error& error) const {
    cl_filter_mode value;
    getInfo(error, CL_SAMPLER_FILTER_MODE, value);
    return value;
}

bool ClSampler::getNormalizedCoords(Error& error) const {
    cl_bool value;
    getInfo(error, CL_SAMPLER_NORMALIZED_COORDS, value);
    return toBool(value);
}

template <typename T>
void ClSampler::getInfo(Error& error,
                        cl_sampler_info paramName,
                        T& value) const {
    cl_int status = clGetSamplerInfo(get(), paramName, sizeof(T), &value, 0);
    clCheckStatus(error, status, "clGetSamplerInfo");
}

void ClSampler::retain() {
    if ( ! isValid) return;
    cl_int status = clRetainSampler(s);
    clCheckStatusPrint(status, "clRetainSampler");
}
void ClSampler::release() {
    if ( ! isValid) return;
    cl_int status = clReleaseSampler(s);
    clCheckStatusPrint(status, "clReleaseSampler");
}
