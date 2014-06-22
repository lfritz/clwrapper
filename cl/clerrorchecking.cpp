#include "clerrorchecking.h"

#include "error.h"

bool clCheckStatus(Error& error, cl_int status, const char * functionName) {
    if (status == CL_SUCCESS)
        return false;
    QString msg = QString("%1 failed with status: %2")
    .arg(functionName)
    .arg(clStatusString(status));
    error.set(msg);
    return true;
}

bool clCheckStatusPrint(cl_int status, const char * functionName) {
    if (status == CL_SUCCESS)
        return false;
    QString msg = QString("%1 failed with status: %2")
    .arg(functionName)
    .arg(clStatusString(status));
    return true;
}

QString clStatusString(cl_int status) {
    switch (status) {
        case CL_SUCCESS: return "success";
        case CL_DEVICE_NOT_FOUND: return "device not found";
        case CL_DEVICE_NOT_AVAILABLE: return "device not available";
        case CL_COMPILER_NOT_AVAILABLE: return "compiler not available";
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        return "memory object allocation failure";
        case CL_OUT_OF_RESOURCES: return "out of resources";
        case CL_OUT_OF_HOST_MEMORY: return "out of host memory";
        case CL_PROFILING_INFO_NOT_AVAILABLE:
        return "profiling info not available";
        case CL_MEM_COPY_OVERLAP: return "mem copy overlap";
        case CL_IMAGE_FORMAT_MISMATCH: return "image format mismatch";
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:
        return "image format not supported";
        case CL_BUILD_PROGRAM_FAILURE: return "build program failure";
        case CL_MAP_FAILURE: return "map failure";
        case CL_INVALID_VALUE: return "invalid value";
        case CL_INVALID_DEVICE_TYPE: return "invalid device type";
        case CL_INVALID_PLATFORM: return "invalid platform";
        case CL_INVALID_DEVICE: return "invalid device";
        case CL_INVALID_CONTEXT: return "invalid context";
        case CL_INVALID_QUEUE_PROPERTIES: return "invalid queue properties";
        case CL_INVALID_COMMAND_QUEUE: return "invalid command queue";
        case CL_INVALID_HOST_PTR: return "invalid host ptr";
        case CL_INVALID_MEM_OBJECT: return "invalid mem object";
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
        return "invalid image format descriptor";
        case CL_INVALID_IMAGE_SIZE: return "invalid image size";
        case CL_INVALID_SAMPLER: return "invalid sampler";
        case CL_INVALID_BINARY: return "invalid binary";
        case CL_INVALID_BUILD_OPTIONS: return "invalid build options";
        case CL_INVALID_PROGRAM: return "invalid program";
        case CL_INVALID_PROGRAM_EXECUTABLE:
        return "invalid program executable";
        case CL_INVALID_KERNEL_NAME: return "invalid kernel name";
        case CL_INVALID_KERNEL_DEFINITION: return "invalid kernel definition";
        case CL_INVALID_KERNEL: return "invalid kernel";
        case CL_INVALID_ARG_INDEX: return "invalid arg index";
        case CL_INVALID_ARG_VALUE: return "invalid arg value";
        case CL_INVALID_ARG_SIZE: return "invalid arg size";
        case CL_INVALID_KERNEL_ARGS: return "invalid kernel args";
        case CL_INVALID_WORK_DIMENSION: return "invalid work dimension";
        case CL_INVALID_WORK_GROUP_SIZE: return "invalid work group size";
        case CL_INVALID_WORK_ITEM_SIZE: return "invalid work item size";
        case CL_INVALID_GLOBAL_OFFSET: return "invalid global offset";
        case CL_INVALID_EVENT_WAIT_LIST: return "invalid event wait list";
        case CL_INVALID_EVENT: return "invalid event";
        case CL_INVALID_OPERATION: return "invalid operation";
        case CL_INVALID_GL_OBJECT: return "invalid gl object";
        case CL_INVALID_BUFFER_SIZE: return "invalid buffer size";
        case CL_INVALID_MIP_LEVEL: return "invalid mip level";
        case CL_INVALID_GLOBAL_WORK_SIZE: return "invalid global work size";
        default:
        return QString("unknown status: %1").arg(status);
    }
}
