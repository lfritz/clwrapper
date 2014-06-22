#pragma once

#include <QList>
#include <QString>
#include <QStringList>
#include <QVector>
#include <glm/glm.hpp>

#include "clew.h"

class ClPlatform;
class Error;

// Wrapper class for OpenCL devices.
class ClDevice {
    cl_device_id id;

public:
    ClDevice();
    ClDevice(cl_device_id deviceId);

    cl_device_id get() const { return id; }
    bool operator==(const ClDevice& other) const { return id == other.id; }
    bool operator!=(const ClDevice& other) const { return id != other.id; }


    // query device

    cl_device_type getType(Error& error) const;
    cl_uint getVendorId(Error& error) const;
    int getMaxComputeUnits(Error& error) const;
    size_t getMaxWorkItemDimensions(Error& error) const;
    QVector<size_t> getMaxWorkItemSizes(Error& error) const;
    size_t getMaxWorkGroupSize(Error& error) const;
    int getPreferredVectorWidthChar(Error& error) const;
    int getPreferredVectorWidthShort(Error& error) const;
    int getPreferredVectorWidthInt(Error& error) const;
    int getPreferredVectorWidthLong(Error& error) const;
    int getPreferredVectorWidthFloat(Error& error) const;
    int getPreferredVectorWidthDouble(Error& error) const;
    int getMaxClockFrequency(Error& error) const;
    int getAddressBits(Error& error) const;

    long int getMaxMemAllocSize(Error& error) const;

    bool getImageSupport(Error& error) const;
    int getMaxReadImageArgs(Error& error) const;
    int getMaxWriteImageArgs(Error& error) const;
    size_t getImage2DMaxWidth(Error& error) const;
    size_t getImage2DMaxHeight(Error& error) const;
    size_t getImage3DMaxWidth(Error& error) const;
    size_t getImage3DMaxHeight(Error& error) const;
    size_t getImage3DMaxDepth(Error& error) const;
    int getMaxSamplers(Error& error) const;

    int getMaxParameterSize(Error& error) const;

    int getMemBaseAddrAlign(Error& error) const;
    int getMinDataTypeAlignSize(Error& error) const;

    cl_device_fp_config getSingleFpConfig(Error& error) const;

    cl_device_mem_cache_type getGlobalMemCacheType(Error& error) const;
    int getGlobalMemCachelineSize(Error& error) const;
    long int getGlobalMemCacheSize(Error& error) const;
    long int getGlobalMemSize(Error& error) const;

    long int getMaxConstantBufferSize(Error& error) const;
    int getMaxConstantArgs(Error& error) const;

    cl_device_local_mem_type getLocalMemType(Error& error) const;
    long int getLocalMemSize(Error& error) const;
    bool getErrorCorrectionSupport(Error& error) const;

    size_t getProfilingTimerResolution(Error& error) const;

    bool getEndianLittle(Error& error) const;
    bool getAvailable(Error& error) const;

    bool getCompilerAvailable(Error& error) const;

    cl_device_exec_capabilities
        getDeviceExecutionCapabilities(Error& error) const;

    cl_command_queue_properties getQueueProperties(Error& error) const;

    ClPlatform getPlatform(Error& error) const;

    QString getName(Error& error) const;
    QString getVendor(Error& error) const;
    QString getDriverVersion(Error& error) const;
    QString getProfile(Error& error) const;
    QString getVersion(Error& error) const;
    QString getExtensions(Error& error) const;


    // high-level querying functions

    QStringList extensionsList(Error& error) const;
    glm::ivec2 image2DMaxDimensions(Error& error) const;
    glm::ivec3 image3DMaxDimensions(Error& error) const;

    long int getGlobalMemSizeMB(Error& error) const;

    bool supportsOutOfOrderExecMode(Error& error) const;
    bool supportsProfiling(Error& error) const;


    // Return all devices of the given type, which should be one of the
    // constants CL_DEVICE_TYPE_CPU, CL_DEVICE_TYPE_GPU,
    // CL_DEVICE_TYPE_ACCELERATOR, CL_DEVICE_TYPE_DEFAULT and
    // CL_DEVICE_TYPE_ALL.
    static QList<ClDevice> getDevices(Error& error, const ClPlatform& platform,
            cl_device_type deviceType=CL_DEVICE_TYPE_ALL);

private:
    template <typename T>
        void getInfo(Error& error, cl_device_info paramName, T& value) const;
    QString getStringInfo(Error& error, cl_device_info paramName) const;
};
