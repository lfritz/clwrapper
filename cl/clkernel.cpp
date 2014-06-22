#include "clkernel.h"

#include "clbuffer.h"
#include "cldevice.h"
#include "clerrorchecking.h"
#include "climage2d.h"
#include "climage3d.h"
#include "clprogram.h"
#include "clsampler.h"
#include "error.h"

ClKernel::ClKernel()
: isValid(false), k(0), name() { }

ClKernel::ClKernel(Error& error, const ClProgram& program, QString kernelName)
: isValid(false), k(0), name(kernelName) {
    cl_int status = CL_SUCCESS;
    k = clCreateKernel(program.get(), qPrintable(name), &status);
    if (status == CL_SUCCESS) {
        isValid = true;
    } else {
        QString msg =
        QString("clCreateKernel for kernel '%1' failed with status: %2")
        .arg(name)
        .arg(clStatusString(status));
        error.set(msg);
    }
}

ClKernel::ClKernel(ClKernel&& rhs)
: isValid(rhs.isValid), k(rhs.k), name(rhs.name) {
    rhs.isValid = false;
}
ClKernel::ClKernel(const ClKernel& rhs)
: isValid(rhs.isValid), k(rhs.k), name(rhs.name) {
    retain();
}

ClKernel& ClKernel::operator=(ClKernel&& rhs) {
    release();
    isValid = rhs.isValid;
    k = rhs.k;
    name = rhs.name;
    rhs.isValid = false;
    return *this;
}
ClKernel& ClKernel::operator=(const ClKernel& rhs) {
    release();
    isValid = rhs.isValid;
    k = rhs.k;
    name = rhs.name;
    retain();
    return *this;
}

ClKernel::~ClKernel() {
    release();
}

QString ClKernel::getFunctionName(Error& error) const {
    cl_int status = CL_SUCCESS;
    size_t size;

    // get size
    status = clGetKernelInfo(k, CL_KERNEL_FUNCTION_NAME, 0, 0, &size);
    clCheckStatus(error, status, "clGetKernelInfo");

    QVector<char> ch((int)size);

    // get character data
    status =
    clGetKernelInfo(k, CL_KERNEL_FUNCTION_NAME, size, ch.data(), 0);
    QString functionName;
    if ( ! clCheckStatus(error, status, "clGetKernelInfo"))
        functionName = ch.data();

    return functionName;
}

int ClKernel::getNumArgs(Error& error) const {
    cl_uint value;
    getInfo<cl_uint>(error, CL_KERNEL_NUM_ARGS, value);
    return value;
}

int ClKernel::getWorkGroupSize(Error& error, const ClDevice& device) const {
    size_t value;
    cl_int status =
    clGetKernelWorkGroupInfo(get(), device.get(),
                             CL_KERNEL_WORK_GROUP_SIZE, sizeof(value), &value,
                             0);
    clCheckStatus(error, status, "clGetKernelWorkGroupInfo");
    return value;
}

ClNDRange ClKernel::getCompileWorkGroupSize(Error& error,
                                            const ClDevice& device) const {
    size_t value[3];
    cl_int status =
    clGetKernelWorkGroupInfo(get(), device.get(),
                             CL_KERNEL_COMPILE_WORK_GROUP_SIZE, sizeof(value),
                             value, 0);
    clCheckStatus(error, status, "clGetKernelWorkGroupInfo");
    return ClNDRange(value[0], value[1], value[2]);
}

quint64 ClKernel::getLocalMemSize(Error& error, const ClDevice& device) const {
    quint64 value;
    cl_int status =
    clGetKernelWorkGroupInfo(get(), device.get(), CL_KERNEL_LOCAL_MEM_SIZE,
                             sizeof(value), &value, 0);
    clCheckStatus(error, status, "clGetKernelWorkGroupInfo");
    return value;
}

void ClKernel::bufferArg(Error& error, cl_uint index, ClBuffer& buffer) const {
    cl_mem m = buffer.get();
    setArg(error, index, sizeof(cl_mem), &m, "buffer");
}

void ClKernel::localBufferArg(Error& error, cl_uint index, size_t size) const {
    setArg(error, index, size, 0, "local buffer size");
}

void ClKernel::imageArg(Error& error, cl_uint index, ClImage2D& image) const {
    cl_mem m = image.get();
    setArg(error, index, sizeof(cl_mem), &m, "2D image");
}

void ClKernel::imageArg(Error& error, cl_uint index, ClImage3D& image) const {
    cl_mem m = image.get();
    setArg(error, index, sizeof(cl_mem), &m, "3D image");
}

void ClKernel::samplerArg(Error& error,
                          cl_uint index,
                          ClSampler& sampler) const {
    cl_sampler s = sampler.get();
    setArg(error, index, sizeof(cl_sampler), &s, "sampler");
}

void ClKernel::charArg(Error& error, cl_uint index, qint8 value) const {
    setScalarArg(error, index, value, "char");
}

void ClKernel::uCharArg(Error& error, cl_uint index, quint8 value) const {
    setScalarArg(error, index, value, "uchar");
}

void ClKernel::shortArg(Error& error, cl_uint index, qint16 value) const {
    setScalarArg(error, index, value, "short");
}

void ClKernel::uShortArg(Error& error, cl_uint index, quint16 value) const {
    setScalarArg(error, index, value, "ushort");
}

void ClKernel::intArg(Error& error, cl_uint index, qint32 value) const {
    setScalarArg(error, index, value, "int");
}

void ClKernel::uIntArg(Error& error, cl_uint index, quint32 value) const {
    setScalarArg(error, index, value, "uint");
}

void ClKernel::longArg(Error& error, cl_uint index, qint64 value) const {
    setScalarArg(error, index, value, "long");
}

void ClKernel::uLongArg(Error& error, cl_uint index, quint64 value) const {
    setScalarArg(error, index, value, "ulong");
}

void ClKernel::floatArg(Error& error, cl_uint index, float value) const {
    setScalarArg(error, index, value, "float");
}

void ClKernel::int2Arg(Error& error, cl_uint index, glm::ivec2 value) const {
    cl_int2 vector;
    cl_int * ptr = reinterpret_cast<cl_int *>(&vector);
    ptr[0] = value.x;
    ptr[1] = value.y;
    setVectorArg(error, index, vector, "cl_int2");
}

void ClKernel::int4Arg(Error& error, cl_uint index, glm::ivec4 value) const {
    cl_int4 vector;
    cl_int * ptr = reinterpret_cast<cl_int *>(&vector);
    ptr[0] = value.x;
    ptr[1] = value.y;
    ptr[2] = value.z;
    ptr[3] = value.w;
    setVectorArg(error, index, vector, "cl_int4");
}

void ClKernel::uint2Arg(Error& error, cl_uint index, glm::uvec2 value) const {
    cl_uint2 vector;
    cl_uint * ptr = reinterpret_cast<cl_uint *>(&vector);
    ptr[0] = value.x;
    ptr[1] = value.y;
    setVectorArg(error, index, vector, "cl_uint2");
}

void ClKernel::uint4Arg(Error& error, cl_uint index, glm::uvec4 value) const {
    cl_uint4 vector;
    cl_uint * ptr = reinterpret_cast<cl_uint *>(&vector);
    ptr[0] = value.x;
    ptr[1] = value.y;
    ptr[2] = value.z;
    ptr[3] = value.w;
    setVectorArg(error, index, vector, "cl_uint4");
}

void ClKernel::float2Arg(Error& error, cl_uint index, glm::vec2 value) const {
    cl_float2 vector;
    cl_float * ptr = reinterpret_cast<cl_float *>(&vector);
    ptr[0] = value.x;
    ptr[1] = value.y;
    setVectorArg(error, index, vector, "cl_float2");
}

void ClKernel::float4Arg(Error& error, cl_uint index, glm::vec4 value) const {
    cl_float4 vector;
    cl_float * ptr = reinterpret_cast<cl_float *>(&vector);
    ptr[0] = value.x;
    ptr[1] = value.y;
    ptr[2] = value.z;
    ptr[3] = value.w;
    setVectorArg(error, index, vector, "cl_float4");
}

template <typename T>
void ClKernel::getInfo(
                       Error& error, cl_kernel_info paramName, T& value) const {
    cl_int status = clGetKernelInfo(k, paramName, sizeof(T), &value, 0);
    clCheckStatus(error, status, "clGetKernelInfo");
}

template <typename T>
void ClKernel::setVectorArg(Error& error, cl_uint index, T& value,
                            const char * typeName) const {
    setArg(error, index, sizeof(T), &value, typeName);
}

template <typename T>
void ClKernel::setScalarArg(Error& error,
                            cl_uint index, T value, const char * type) const {
    setArg(error, index, sizeof(T), &value, type);
}

void ClKernel::setArg(Error& error,
                      cl_uint index, size_t argSize, const void * argValue,
                      const char *type) const {
    cl_int status = clSetKernelArg(k, index, argSize, argValue);
    if (status != CL_SUCCESS)
        error.set(QString("clSetKernelArg failed with status: %1 when setting "
                  "argument %2 of kernel %3 to %4 value")
    .arg(clStatusString(status))
    .arg(index).arg(name).arg(type));
}

void ClKernel::retain() {
    if ( ! isValid) return;
    cl_int status = clRetainKernel(k);
    clCheckStatusPrint(status, "clRetainKernel");
}
void ClKernel::release() {
    if ( ! isValid) return;
    cl_int status = clReleaseKernel(k);
    clCheckStatusPrint(status, "clReleaseKernel");
}
