#include "clcontext.h"

#include <QVector>

#include "cldevice.h"
#include "clerrorchecking.h"
#include "clplatform.h"
#include "error.h"

ClContext::ClContext() : isValid(false), c(0) { }

ClContext::ClContext(Error& error, const ClPlatform& platform,
                     const ClDevice& device)
: isValid(false), c(0) {
    cl_int status = CL_SUCCESS;
    cl_context_properties properties[3] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platform.get(),
        0
    };
    cl_device_id deviceId = device.get();
    c = clCreateContext(properties, 1, &deviceId, 0, 0, &status);
    if (status == CL_SUCCESS)
        isValid = true;
    else
        clCheckStatus(error, status, "clCreateContext");
}

ClContext::ClContext(Error& error, const ClPlatform& platform,
                     const QList<ClDevice> devices)
: isValid(false), c(0) {
    QVector<cl_device_id> deviceIds;
    foreach (ClDevice d, devices)
        deviceIds.append(d.get());
    cl_int status = CL_SUCCESS;
    cl_context_properties properties[3] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platform.get(),
        0
    };
    c = clCreateContext(
            properties, deviceIds.size(), deviceIds.data(), 0, 0, &status);
    if (status == CL_SUCCESS)
        isValid = true;
    else
        clCheckStatus(error, status, "clCreateContext");
}

ClContext::ClContext(Error& error, const ClPlatform& platform,
                     cl_device_type deviceType)
: isValid(false), c(0) {
    cl_int status = CL_SUCCESS;
    cl_context_properties properties[3] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platform.get(),
        0
    };
    c = clCreateContextFromType(properties, deviceType, 0, 0, &status);
    if (status == CL_SUCCESS)
        isValid = true;
    else
        clCheckStatus(error, status, "clCreateContextFromType");
}

ClContext::ClContext(ClContext&& rhs) : isValid(rhs.isValid), c(rhs.c) {
    rhs.isValid = false;
}
ClContext::ClContext(const ClContext& rhs) : isValid(rhs.isValid), c(rhs.c) {
    retain();
}

ClContext& ClContext::operator=(ClContext&& rhs) {
    release();
    isValid = rhs.isValid;
    c = rhs.c;
    rhs.isValid = false;
    return *this;
}
ClContext& ClContext::operator=(const ClContext& rhs) {
    release();
    isValid = rhs.isValid;
    c = rhs.c;
    retain();
    return *this;
}

ClContext::~ClContext() {
    release();
}

QList<ClDevice> ClContext::getDevices(Error& error) const {
    // get number of devices
    size_t size = getInfoSize(error, CL_CONTEXT_DEVICES);
    if (error) return QList<ClDevice>();
    int nDevices = (int)(size / sizeof(cl_device_id));

    // query device ids
    QVector<cl_device_id> ids(nDevices);
    getInfoArray(error, CL_CONTEXT_DEVICES, ids.data(), size);
    if (error) return QList<ClDevice>();

    // create ClDevice objects
    QList<ClDevice> devices;
    foreach(cl_device_id id, ids)
        devices << id;
    return devices;
}

size_t ClContext::getInfoSize(Error& error, cl_context_info paramName) const {
    size_t size = 0;
    cl_int status = clGetContextInfo(c, paramName, 0, 0, &size);
    clCheckStatus(error, status, "clGetContextInfo");
    return size;
}

void ClContext::getInfoArray(Error& error, cl_context_info paramName,
                             void * data, size_t size) const {
    cl_int status = clGetContextInfo(c, paramName, size, data, 0);
    clCheckStatus(error, status, "clGetContextInfo");
}

void ClContext::retain() {
    if ( ! isValid) return;
    cl_int status = clRetainContext(c);
    clCheckStatusPrint(status, "clRetainContext");
}
void ClContext::release() {
    if ( ! isValid) return;
    cl_int status = clReleaseContext(c);
    clCheckStatusPrint(status, "clReleaseContext");
}
