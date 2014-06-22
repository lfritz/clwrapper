#include "cldevice.h"

#include <QVector>

#include "clbool.h"
#include "clerrorchecking.h"
#include "clplatform.h"
#include "error.h"

using glm::ivec2;
using glm::ivec3;

ClDevice::ClDevice() { }

ClDevice::ClDevice(cl_device_id deviceId) : id(deviceId) { }

cl_device_type ClDevice::getType(Error& error) const {
    cl_device_type value = 0;
    getInfo<cl_device_type>(error, CL_DEVICE_TYPE, value);
    return value;
}
cl_uint ClDevice::getVendorId(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_VENDOR_ID, value);
    return value;
}
int ClDevice::getMaxComputeUnits(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_MAX_COMPUTE_UNITS, value);
    return value;
}

size_t ClDevice::getMaxWorkItemDimensions(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_MAX_WORK_GROUP_SIZE, value);
    return value;
}

QVector<size_t> ClDevice::getMaxWorkItemSizes(Error& error) const {
    size_t size = getMaxWorkItemDimensions(error);
    if (error) return QVector<size_t>();
    QVector<size_t> v(size);
    cl_int status =
    clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_SIZES,
                    size * sizeof(size_t), v.data(), 0);
    clCheckStatus(error, status, "clGetDeviceInfo");
    return v;
}

size_t ClDevice::getMaxWorkGroupSize(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_MAX_WORK_GROUP_SIZE, value);
    return value;
}

int ClDevice::getPreferredVectorWidthChar(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, value);
    return value;
}
int ClDevice::getPreferredVectorWidthShort(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, value);
    return value;
}
int ClDevice::getPreferredVectorWidthInt(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, value);
    return value;
}
int ClDevice::getPreferredVectorWidthLong(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, value);
    return value;
}
int ClDevice::getPreferredVectorWidthFloat(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, value);
    return value;
}
int ClDevice::getPreferredVectorWidthDouble(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, value);
    return value;
}

int ClDevice::getMaxClockFrequency(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_MAX_CLOCK_FREQUENCY, value);
    return value;
}

int ClDevice::getAddressBits(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_ADDRESS_BITS, value);
    return value;
}

long int ClDevice::getMaxMemAllocSize(Error& error) const {
    cl_ulong value = 0;
    getInfo<cl_ulong>(error, CL_DEVICE_MAX_MEM_ALLOC_SIZE, value);
    return value;
}

bool ClDevice::getImageSupport(Error& error) const {
    cl_bool value = false;
    getInfo<cl_bool>(error, CL_DEVICE_IMAGE_SUPPORT, value);
    return toBool(value);
}

int ClDevice::getMaxReadImageArgs(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_MAX_READ_IMAGE_ARGS, value);
    return (int)value;
}

int ClDevice::getMaxWriteImageArgs(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, value);
    return (int)value;
}

size_t ClDevice::getImage2DMaxWidth(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_IMAGE2D_MAX_WIDTH, value);
    return value;
}

size_t ClDevice::getImage2DMaxHeight(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_IMAGE2D_MAX_HEIGHT, value);
    return value;
}

size_t ClDevice::getImage3DMaxWidth(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_IMAGE3D_MAX_WIDTH, value);
    return value;
}

size_t ClDevice::getImage3DMaxHeight(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_IMAGE3D_MAX_HEIGHT, value);
    return value;
}

size_t ClDevice::getImage3DMaxDepth(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_IMAGE3D_MAX_DEPTH, value);
    return value;
}

int ClDevice::getMaxSamplers(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_MAX_SAMPLERS, value);
    return value;
}

int ClDevice::getMaxParameterSize(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_MAX_PARAMETER_SIZE, value);
    return value;
}

int ClDevice::getMemBaseAddrAlign(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_MEM_BASE_ADDR_ALIGN, value);
    return value;
}

int ClDevice::getMinDataTypeAlignSize(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE, value);
    return value;
}

cl_device_fp_config ClDevice::getSingleFpConfig(Error& error) const {
    cl_device_fp_config value = 0;
    getInfo<cl_device_fp_config>(error, CL_DEVICE_SINGLE_FP_CONFIG, value);
    return value;
}

cl_device_mem_cache_type ClDevice::getGlobalMemCacheType(Error& error) const {
    cl_device_mem_cache_type value = CL_NONE;
    getInfo<cl_device_mem_cache_type>(error,
                                      CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
                                      value);
    return value;
}

int ClDevice::getGlobalMemCachelineSize(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, value);
    return value;
}

long int ClDevice::getGlobalMemCacheSize(Error& error) const {
    cl_ulong value = 0;
    getInfo<cl_ulong>(error, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, value);
    return value;
}

long int ClDevice::getGlobalMemSize(Error& error) const {
    cl_ulong value = 0;
    getInfo<cl_ulong>(error, CL_DEVICE_GLOBAL_MEM_SIZE, value);
    return value;
}

long int ClDevice::getMaxConstantBufferSize(Error& error) const {
    cl_ulong value = 0;
    getInfo<cl_ulong>(error, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, value);
    return value;
}

int ClDevice::getMaxConstantArgs(Error& error) const {
    cl_uint value = 0;
    getInfo<cl_uint>(error, CL_DEVICE_MAX_CONSTANT_ARGS, value);
    return value;
}

cl_device_local_mem_type ClDevice::getLocalMemType(Error& error) const {
    cl_device_local_mem_type value = CL_LOCAL;
    getInfo<cl_device_local_mem_type>(error, CL_DEVICE_LOCAL_MEM_TYPE, value);
    return value;
}

long int ClDevice::getLocalMemSize(Error& error) const {
    cl_ulong value = 0;
    getInfo<cl_ulong>(error, CL_DEVICE_LOCAL_MEM_SIZE, value);
    return value;
}

bool ClDevice::getErrorCorrectionSupport(Error& error) const {
    cl_bool value = false;
    getInfo<cl_bool>(error, CL_DEVICE_ERROR_CORRECTION_SUPPORT, value);
    return toBool(value);
}

size_t ClDevice::getProfilingTimerResolution(Error& error) const {
    size_t value = 0;
    getInfo<size_t>(error, CL_DEVICE_PROFILING_TIMER_RESOLUTION, value);
    return value;
}

bool ClDevice::getEndianLittle(Error& error) const {
    cl_bool value = false;
    getInfo<cl_bool>(error, CL_DEVICE_ENDIAN_LITTLE, value);
    return toBool(value);
}

bool ClDevice::getAvailable(Error& error) const {
    cl_bool value = false;
    getInfo<cl_bool>(error, CL_DEVICE_AVAILABLE, value);
    return toBool(value);
}

bool ClDevice::getCompilerAvailable(Error& error) const {
    cl_bool value = false;
    getInfo<cl_bool>(error, CL_DEVICE_COMPILER_AVAILABLE, value);
    return toBool(value);
}

cl_device_exec_capabilities
ClDevice::getDeviceExecutionCapabilities(Error& error) const {
    cl_device_exec_capabilities value = 0;
    getInfo<cl_device_exec_capabilities>(error,
                                         CL_DEVICE_EXECUTION_CAPABILITIES,
                                         value);
    return value;
}

cl_command_queue_properties ClDevice::getQueueProperties(Error& error) const {
    cl_command_queue_properties properties = 0;
    getInfo(error, CL_DEVICE_QUEUE_PROPERTIES, properties);
    return properties;
}

ClPlatform ClDevice::getPlatform(Error& error) const {
    cl_platform_id value;
    getInfo<cl_platform_id>(error, CL_DEVICE_PLATFORM, value);
    if (error) return ClPlatform();
    return ClPlatform(value);
}

QString ClDevice::getName(Error& error) const {
    return getStringInfo(error, CL_DEVICE_NAME);
}

QString ClDevice::getVendor(Error& error) const {
    return getStringInfo(error, CL_DEVICE_VENDOR);
}

QString ClDevice::getDriverVersion(Error& error) const {
    return getStringInfo(error, CL_DRIVER_VERSION);
}

QString ClDevice::getProfile(Error& error) const {
    return getStringInfo(error, CL_DEVICE_PROFILE);
}

QString ClDevice::getVersion(Error& error) const {
    return getStringInfo(error, CL_DEVICE_VERSION);
}

QString ClDevice::getExtensions(Error& error) const {
    return getStringInfo(error, CL_DEVICE_EXTENSIONS);
}

QStringList ClDevice::extensionsList(Error& error) const {
    QString s = getExtensions(error);
    if (error) return QStringList();
    return s.split(' ', QString::SkipEmptyParts);
}

ivec2 ClDevice::image2DMaxDimensions(Error& error) const {
    size_t maxWidth  = getImage2DMaxWidth(error);  if (error) return ivec2(0);
    size_t maxHeight = getImage2DMaxHeight(error); if (error) return ivec2(0);
    return ivec2(maxWidth, maxHeight);
}

ivec3 ClDevice::image3DMaxDimensions(Error& error) const {
    size_t maxWidth  = getImage3DMaxWidth(error);  if (error) return ivec3(0);
    size_t maxHeight = getImage3DMaxHeight(error); if (error) return ivec3(0);
    size_t maxDepth  = getImage3DMaxDepth(error);  if (error) return ivec3(0);
    return ivec3(maxWidth, maxHeight, maxDepth);
}

long int ClDevice::getGlobalMemSizeMB(Error& error) const {
    long int bytes = getGlobalMemSize(error);
    if (error) return 0;
    return bytes / (1024*1024);
}

bool ClDevice::supportsOutOfOrderExecMode(Error& error) const {
    return getQueueProperties(error) & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;
}

bool ClDevice::supportsProfiling(Error& error) const {
    return getQueueProperties(error) & CL_QUEUE_PROFILING_ENABLE;
}

QList<ClDevice> ClDevice::getDevices(Error& error, const ClPlatform& platform,
                                     cl_device_type deviceType) {
    QList<ClDevice> devices;

    // get number of devices
    cl_uint n;
    cl_int status = clGetDeviceIDs(platform.get(), deviceType, 0, 0, &n);
    if (status == CL_DEVICE_NOT_FOUND || n == 0)
        return QList<ClDevice>(); // no devices found -- return empty list
    clCheckStatus(error, status, "clGetDeviceIDs");
    if (error) return devices;

    // get device ids
    QVector<cl_device_id> deviceIDs(n);
    status = clGetDeviceIDs(platform.get(), deviceType, n, deviceIDs.data(), 0);
    clCheckStatus(error, status, "clGetDeviceIDs");
    if (error) return devices;

    // create ClDevice objects
    for (cl_uint i = 0; i < n; ++i)
        devices.append(ClDevice(deviceIDs[i]));

    return devices;
}

template <typename T>
void ClDevice::getInfo(Error& error, cl_device_info paramName, T& value) const {
    cl_int status = clGetDeviceInfo(id, paramName, sizeof(T), &value, 0);
    clCheckStatus(error, status, "clGetDeviceInfo");
}

QString ClDevice::getStringInfo(Error& error, cl_device_info paramName) const {
    cl_int status = CL_SUCCESS;
    size_t size;

    // get size
    status = clGetDeviceInfo(id, paramName, 0, 0, &size);
    clCheckStatus(error, status, "clGetDeviceInfo");
    if (error) return "";

    QVector<char> ch((int)size);

    // get character data
    status = clGetDeviceInfo(id, paramName, size, ch.data(), 0);
    QString info;
    if ( ! clCheckStatus(error, status, "clGetDeviceInfo"))
        info = ch.data();

    return info;
}
