#include "clmem.h"

#include "clerrorchecking.h"
#include "error.h"

ClMem::ClMem()
: isValid(false), m(0) { }

ClMem::ClMem(ClMem&& rhs)
: isValid(rhs.isValid), m(rhs.m) {
    rhs.isValid = false;
}

ClMem::ClMem(const ClMem& rhs)
: isValid(rhs.isValid), m(rhs.m) {
    retain();
}

ClMem& ClMem::operator=(ClMem&& rhs) {
    release();
    isValid = rhs.isValid;
    m = rhs.m;
    rhs.isValid = false;
    return *this;
}
ClMem& ClMem::operator=(const ClMem& rhs) {
    release();
    isValid = rhs.isValid;
    m = rhs.m;
    retain();
    return *this;
}

ClMem::~ClMem() {
    release();
}

void ClMem::set(cl_mem mem) {
    release();
    isValid = true;
    m = mem;
}

cl_mem_object_type ClMem::getType(Error& error) const {
    cl_mem_object_type value;
    getInfo<cl_mem_object_type>(error, CL_MEM_TYPE, value);
    return value;
}

cl_mem_flags ClMem::getFlags(Error& error) const {
    cl_mem_flags value;
    getInfo<cl_mem_flags>(error, CL_MEM_FLAGS, value);
    return value;
}

size_t ClMem::getSize(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_MEM_SIZE, value);
    return value;
}

void * ClMem::getHostPtr(Error& error) const {
    void * value = 0;
    getInfo<void *>(error, CL_MEM_HOST_PTR, value);
    return value;
}

template <typename T>
void ClMem::getInfo(Error& error, cl_mem_info paramName, T& value) const {
    cl_int status = clGetMemObjectInfo(get(), paramName, sizeof(T), &value, 0);
    clCheckStatus(error, status, "clGetMemObjectInfo");
}

void ClMem::retain() {
    if ( ! isValid) return;
    cl_int status = clRetainMemObject(m);
    clCheckStatusPrint(status, "clRetainMemObject");
}
void ClMem::release() {
    if ( ! isValid) return;
    cl_int status = clReleaseMemObject(m);
    clCheckStatusPrint(status, "clReleaseMemObject");
}
