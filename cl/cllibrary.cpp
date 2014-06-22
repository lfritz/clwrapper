#include "cllibrary.h"

#include <QVector>
#include <QtGlobal> // for Q_OS_WIN32 and Q_OS_MAC

#include "clerrorchecking.h"
#include "error.h"

ClLibrary::ClLibrary() {
    status = clewInit(filename());
}

const char * ClLibrary::filename() const {
#ifdef Q_OS_WIN32
    return "opencl.dll";
#else
#ifdef Q_OS_MAC
    return "/System/Library/Frameworks/OpenCL.framework/OpenCL";
#else
    return "libOpenCL.so";
#endif
#endif
}

QList<ClPlatform> ClLibrary::platforms(Error& error) const {
    cl_int status = CL_SUCCESS;
    QList<ClPlatform> platforms;

    // get number of platforms
    cl_uint numPlatforms;
    status = clGetPlatformIDs(0, 0, &numPlatforms);
    clCheckStatus(error, status, "clGetPlatformIDs");
    if (error) return platforms;

    // get platform ids
    QVector<cl_platform_id> platformIDs(numPlatforms);
    status = clGetPlatformIDs(numPlatforms, platformIDs.data(), 0);
    clCheckStatus(error, status, "clGetPlatformIDs");
    if (error) return platforms;

    // create ClPlatform objects
    for (cl_uint i = 0; i < numPlatforms; ++i)
        platforms.append(ClPlatform(platformIDs[i]));

    return platforms;
}
