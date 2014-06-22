#include "clbuffer.h"

#include "clcontext.h"
#include "clerrorchecking.h"

ClBuffer::ClBuffer() : ClMem(), sizeBytes(0) { }

ClBuffer::ClBuffer(Error& error, const ClContext& context, size_t sz,
                   ClMemAccess memAccess, bool allocHostPtr)
: ClMem(), sizeBytes(sz) {
    init(error, context, sz, 0, memAccess, allocHostPtr);
}

ClBuffer::ClBuffer(Error& error, const ClContext& context, size_t sz,
                   void * copyFrom,
                   ClMemAccess memAccess, bool allocHostPtr)
: ClMem(), sizeBytes(sz) {
    init(error, context, sz, copyFrom, memAccess, allocHostPtr);
}

void ClBuffer::init(Error& error, const ClContext& context, size_t sz,
                    void * copyFrom, ClMemAccess memAccess,
                    bool allocHostPtr) {
    cl_mem_flags flags = 0;
    if (copyFrom)                 flags |= CL_MEM_COPY_HOST_PTR;
    if (memAccess == clWriteOnly) flags |= CL_MEM_WRITE_ONLY;
    if (memAccess == clReadOnly)  flags |= CL_MEM_READ_ONLY;
    if (allocHostPtr)             flags |= CL_MEM_ALLOC_HOST_PTR;
    cl_int status = CL_SUCCESS;
    cl_mem mem = clCreateBuffer(context.get(), flags, sz, copyFrom, &status);
    if (status == CL_SUCCESS)
        set(mem);
    else
        clCheckStatus(error, status, "clCreateBuffer");
}
