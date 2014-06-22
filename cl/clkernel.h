#pragma once

#include <QString>
#include <glm/glm.hpp>

#include "clew.h"
#include "clndrange.h"

class ClBuffer;
class ClContext;
class ClDevice;
class ClImage2D;
class ClImage3D;
class ClProgram;
class ClSampler;
class Error;

// Wrapper class for OpenCL kernel objects.
class ClKernel {
    bool isValid;
    cl_kernel k;
    QString name;

public:
    ClKernel();
    ClKernel(Error& error, const ClProgram& program, QString kernelName);

    // move and copy constructors
    ClKernel(ClKernel&& rhs);
    ClKernel(const ClKernel& rhs);

    // move and copy assignment
    ClKernel& operator=(ClKernel&& rhs);
    ClKernel& operator=(const ClKernel& rhs);

    ~ClKernel();

    QString kernelName() const { return name; }
    cl_kernel get() const { return k; }

    // query kernel info
    QString getFunctionName(Error& error) const;
    int getNumArgs(Error& error) const;
    // missing: get context
    // missing: get program

    // query kernel work-group info
    int getWorkGroupSize(Error& error, const ClDevice& device) const;
    ClNDRange getCompileWorkGroupSize(Error& error,
                                      const ClDevice& device) const;
    quint64 getLocalMemSize(Error& error, const ClDevice& device) const;

    // set kernel arguments
    void bufferArg(Error& error, cl_uint index, ClBuffer& buffer) const;
    void localBufferArg(Error& error, cl_uint index, size_t size) const;

    void imageArg(Error& error, cl_uint index, ClImage2D& buffer) const;
    void imageArg(Error& error, cl_uint index, ClImage3D& buffer) const;

    void samplerArg(Error& error, cl_uint index, ClSampler& sampler) const;

    void charArg(Error& error, cl_uint index, qint8 value) const;
    void uCharArg(Error& error, cl_uint index, quint8 value) const;
    void shortArg(Error& error, cl_uint index, qint16 value) const;
    void uShortArg(Error& error, cl_uint index, quint16 value) const;
    void intArg(Error& error, cl_uint index, qint32 value) const;
    void uIntArg(Error& error, cl_uint index, quint32 value) const;
    void longArg(Error& error, cl_uint index, qint64 value) const;
    void uLongArg(Error& error, cl_uint index, quint64 value) const;
    void floatArg(Error& error, cl_uint index, float value) const;
    // (Kernel arguments of type bool or size_t are not allowed.)

    void int2Arg(Error& error, cl_uint index, glm::ivec2 value) const;
    void int4Arg(Error& error, cl_uint index, glm::ivec4 value) const;
    void uint2Arg(Error& error, cl_uint index, glm::uvec2 value) const;
    void uint4Arg(Error& error, cl_uint index, glm::uvec4 value) const;
    void float2Arg(Error& error, cl_uint index, glm::vec2 value) const;
    void float4Arg(Error& error, cl_uint index, glm::vec4 value) const;

private:
    template <typename T>
    void getInfo(
                 Error& error, cl_kernel_info paramName, T& value) const;
    template <typename T>
    void setVectorArg(Error& error,
                      cl_uint index, T& value, const char * typeName) const;
    template <typename T>
    void setScalarArg(Error& error,
                      cl_uint index, T value, const char * type) const;
    void setArg(Error& error, cl_uint index, size_t argSize,
                const void * argValue, const char * type) const;

    void retain();
    void release();
};
