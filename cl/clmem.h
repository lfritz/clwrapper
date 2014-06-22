#pragma once

#include "clew.h"

class Error;

// Abstract base class for buffer and image objects.
class ClMem {
    bool isValid;
    cl_mem m;

public:
    virtual ~ClMem();

    cl_mem get() const { return m; }

    cl_mem_object_type getType(Error& error) const;
    cl_mem_flags getFlags(Error& error) const;
    size_t getSize(Error& error) const;
    void * getHostPtr(Error& error) const;

    // missing: get context

protected:
    ClMem();

    // move and copy constructors
    ClMem(ClMem&& rhs);
    ClMem(const ClMem& rhs);

    // move and copy assignment
    ClMem& operator=(ClMem&& rhs);
    ClMem& operator=(const ClMem& rhs);

    void set(cl_mem mem);

private:
    template <typename T>
    void getInfo(Error& error, cl_mem_info paramName, T& value) const;

    void retain();
    void release();
};
