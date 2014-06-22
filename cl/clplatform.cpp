#include "clplatform.h"

#include <QVector>

#include "clerrorchecking.h"
#include "error.h"

ClPlatform::ClPlatform() { }

ClPlatform::ClPlatform(cl_platform_id platformId) : id(platformId) { }

QString ClPlatform::getProfile(Error& error) const {
    return getStringInfo(error, CL_PLATFORM_PROFILE);
}
QString ClPlatform::getVersion(Error& error) const {
    return getStringInfo(error, CL_PLATFORM_VERSION);
}
QString ClPlatform::getName(Error& error) const {
    return getStringInfo(error, CL_PLATFORM_NAME);
}
QString ClPlatform::getVendor(Error& error) const {
    return getStringInfo(error, CL_PLATFORM_VENDOR);
}
QString ClPlatform::getExtensions(Error& error) const {
    return getStringInfo(error, CL_PLATFORM_EXTENSIONS);
}

QStringList ClPlatform::extensionsList(Error& error) const {
    QString s = getExtensions(error);
    if (error) return QStringList();
    return s.split(' ', QString::SkipEmptyParts);
}

QString ClPlatform::getStringInfo(Error& error,
                                  cl_platform_info paramName) const {
    cl_int status = CL_SUCCESS;
    size_t size;

    // get size
    status = clGetPlatformInfo(id, paramName, 0, 0, &size);
    clCheckStatus(error, status, "clGetPlatformInfo");
    if (error) return "";

    QVector<char> ch((int)size);

    // get character data
    status = clGetPlatformInfo(id, paramName, size, ch.data(), 0);
    QString info;
    if ( ! clCheckStatus(error, status, "clGetPlatformInfo"))
        info = ch.data();

    return info;
}
