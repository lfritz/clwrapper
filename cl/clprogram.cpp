#include "clprogram.h"

#include <QFile>
#include <QTextStream>
#include <QVector>

#include "clcontext.h"
#include "cldevice.h"
#include "clerrorchecking.h"
#include "error.h"

ClProgram::ClProgram() : isValid(false), p(0) { }

ClProgram::ClProgram(ClProgram&& rhs) : isValid(rhs.isValid), p(rhs.p) {
    rhs.isValid = false;
}

ClProgram::ClProgram(const ClProgram& rhs) : isValid(rhs.isValid), p(rhs.p) {
    retain();
}

ClProgram& ClProgram::operator=(ClProgram&& rhs) {
    release();
    isValid = rhs.isValid;
    p = rhs.p;
    rhs.isValid = false;
    return *this;
}
ClProgram& ClProgram::operator=(const ClProgram& rhs) {
    release();
    isValid = rhs.isValid;
    p = rhs.p;
    retain();
    return *this;
}

ClProgram::~ClProgram() {
    release();
}

ClProgram::ClProgram(Error& error, const ClContext& context, QString name) {
    // open file
    QFile file(name);
    if ( ! file.open(QIODevice::ReadOnly)) {
        QString msg = QString("cannot open %1 for reading: %2")
        .arg(file.fileName())
        .arg(file.errorString());
        error.set(msg);
        return;
    }

    // read in source code
    QTextStream in(&file);
    QString qs = in.readAll();
    file.close();
    QByteArray ba = qs.toLatin1();
    const char * source = ba.data();

    // create cl_program object
    cl_int status = CL_SUCCESS;
    p = clCreateProgramWithSource(context.get(), 1, &source, 0, &status);
    if (status == CL_SUCCESS)
        isValid = true;
    else
        clCheckStatus(error, status, "clCreateProgramWithSource");
}

ClProgram::ClProgram(Error& error, const ClContext& context,
                     const ClDevice& device, QByteArray bytes) {
    cl_int status = CL_SUCCESS;
    cl_int binaryStatus = CL_SUCCESS;

    cl_device_id deviceId = device.get();
    size_t size = (size_t)bytes.size();
    const unsigned char * binary = (unsigned char *)bytes.constData();
    p = clCreateProgramWithBinary(
                                  context.get(), 1, &deviceId, &size, &binary,
                                  &binaryStatus, &status);
    if (status == CL_SUCCESS) {
        isValid = true;
    } else {
        if (binaryStatus != CL_SUCCESS) {
            error.set("could not load program binary");
            return;
        }
        clCheckStatus(error, status, "clCreateProgramWithBinary");
    }
}

typedef QPair<ClDevice, QByteArray> DeviceBinaryPair;

ClProgram::ClProgram(Error& error, const ClContext& context,
                     QList<DeviceBinaryPair> pairs) {
    cl_int status = CL_SUCCESS;
    cl_int binaryStatus = CL_SUCCESS;

    // create argument vectors
    cl_uint numDevices = (cl_uint)pairs.size();
    QVector<cl_device_id> deviceVector;
    QVector<size_t> lengthVector;
    QVector<const unsigned char *> ptrVector;
    foreach (const DeviceBinaryPair &pair, pairs) {
        deviceVector << pair.first.get();
        lengthVector << (size_t)pair.second.size();
        ptrVector << (const unsigned char *)pair.second.constData();
    }

    // create program
    p = clCreateProgramWithBinary(context.get(), numDevices,
                                  deviceVector.constData(),
                                  lengthVector.constData(),
                                  ptrVector.data(),
                                  &binaryStatus, &status);
    if (status == CL_SUCCESS) {
        isValid = true;
    } else {
        if (binaryStatus != CL_SUCCESS) {
            error.set("could not load program binaries");
            return;
        }
        clCheckStatus(error, status, "clCreateProgramWithBinary");
    }
}

void ClProgram::build(Error& error, const ClDevice& device,
                      const char * options) {
    QList<ClDevice> devices;
    devices << device;
    build(error, devices, options);
}

void ClProgram::build(Error& error, QList<ClDevice> devices,
                      const char * options) {
    QVector<cl_device_id> deviceIds;
    foreach (ClDevice device, devices) {
        deviceIds << device.get();
    }
    cl_int status = clBuildProgram(p, deviceIds.size(), deviceIds.data(),
                                   options, 0, 0);
    if (status == CL_BUILD_PROGRAM_FAILURE) {
        QString msg = QString("clBuildProgram failed with status: %1\n")
        .arg(clStatusString(status));
        foreach (ClDevice device, devices) {
            msg.append("build status: ");
            msg.append(buildStatusString(error, device));
            msg.append("\n");
            msg.append("build options: ");
            msg.append(buildOptions(error, device));
            msg.append("\n");
            msg.append("build log:\n");
            msg.append(buildLog(error, device));
        }
        error.set(msg);
    } else {
        clCheckStatus(error, status, "clBuildProgram");
    }
}

cl_build_status ClProgram::buildStatus(Error& error, const ClDevice& device) {
    cl_int status = CL_SUCCESS;
    cl_build_status bs;
    status = clGetProgramBuildInfo(
                                   p, device.get(), CL_PROGRAM_BUILD_STATUS,
                                   sizeof(cl_build_status), &bs, 0);
    clCheckStatus(error, status, "clGetProgramBuildInfo");
    return bs;
}

QString ClProgram::buildStatusString(Error& error, const ClDevice& device) {
    cl_build_status s = buildStatus(error, device);
    if (error) return "";

    switch (s) {
        case CL_BUILD_NONE:
        return "none (no build has been performed)";
        case CL_BUILD_ERROR:
        return "error";
        case CL_BUILD_SUCCESS:
        return "success";
        case CL_BUILD_IN_PROGRESS:
        return "in progress";
    }
    return QString("unknown build status: %1").arg(s);
}

QString ClProgram::buildOptions(Error& error, const ClDevice& device) {
    return buildInfo(error, CL_PROGRAM_BUILD_OPTIONS, device);
}

QString ClProgram::buildLog(Error& error, const ClDevice& device) {
    return buildInfo(error, CL_PROGRAM_BUILD_LOG, device);
}

// Return the program binary for the given device. Returns a null byte array if
// the program has not been built for this device.
QByteArray ClProgram::getBinary(Error& error, const ClDevice& device) {
    // this method is a bit inefficient, but retrieving binary code is probably
    // not a common operation, so I decided that simplicity was more important

    // find out the number of devices
    cl_uint nDevicesUint;
    getInfo<cl_uint>(error, CL_PROGRAM_NUM_DEVICES, &nDevicesUint);
    if (error) return QByteArray();
    int nDevices = (int)nDevicesUint;

    // get the list of devices associated with the program object
    QVector<cl_device_id> devices(nDevices);
    getInfoArray(error, CL_PROGRAM_DEVICES, devices.data(),
                 nDevices * sizeof(cl_device_id));
    if (error) return QByteArray();

    // get the size of the program binary for each device
    QVector<size_t> binarySizes(nDevices);
    getInfoArray(error, CL_PROGRAM_BINARY_SIZES, binarySizes.data(),
                 nDevices * sizeof(size_t));
    if (error) return QByteArray();

    // get program binaries
    QVector< QVector<quint8> > binaryData(nDevices);
    QVector<quint8 *> binaryPointers(nDevices);
    for (int i = 0; i < nDevices; ++i) {
        binaryData[i].resize((int)binarySizes[i]);
        binaryPointers[i] = binaryData[i].data();
    }
    getInfoArray(error, CL_PROGRAM_BINARIES, binaryPointers.data(),
                 nDevices * sizeof(quint8 *));
    if (error) return QByteArray();

    // find the binary we want and return it as QByteArray
    for (int i = 0; i < nDevices; ++i)
        if (devices[i] == device.get())
            return QByteArray((const char *)binaryData[i].data(),
                              (int)binarySizes[i]);

        return QByteArray();
    }

template <typename T>
void ClProgram::getInfo(Error& error,
                        cl_program_info paramName, T * value) const {
    cl_int status = clGetProgramInfo(p, paramName, sizeof(T), value, 0);
    clCheckStatus(error, status, "clGetProgramInfo");
}

void ClProgram::getInfoArray(Error& error, cl_program_info paramName,
                             void * data, size_t size) const {
    cl_int status = clGetProgramInfo(p, paramName, size, data, 0);
    clCheckStatus(error, status, "clGetProgramInfo");
}

QString ClProgram::buildInfo(Error& error, cl_program_build_info paramName,
                             const ClDevice& device) {
    cl_int status = CL_SUCCESS;
    size_t size;

    // get size
    status = clGetProgramBuildInfo(
                                   p, device.get(), paramName, 0, 0, &size);
    clCheckStatus(error, status, "clGetProgramBuildInfo");
    if (error) return "";

    // get character data
    QByteArray ch((int)size, 0);
    status = clGetProgramBuildInfo(p, device.get(), paramName, size,
                                   ch.data(), 0);
    clCheckStatus(error, status, "clGetProgramBuildInfo");
    if (error) return "";

    return QString(ch);
}

void ClProgram::retain() {
    if ( ! isValid) return;
    cl_int status = clRetainProgram(p);
    clCheckStatusPrint(status, "clRetainProgram");
}
void ClProgram::release() {
    if ( ! isValid) return;
    cl_int status = clReleaseProgram(p);
    clCheckStatusPrint(status, "clReleaseProgram");
}
