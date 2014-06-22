#include "clkerneltest.h"

#include <clbuffer.h>
#include <clcommandqueue.h>
#include <clkernel.h>
#include <clndrange.h>
#include <clndrangekernel.h>
#include <clplatform.h>
#include <clreadbuffer.h>
#include <cltask.h>

#include "errorassert.h"

ClKernelTest::ClKernelTest() : NeedsClCommandQueue(), error(), program() { }

ClKernelTest::~ClKernelTest() { }

void ClKernelTest::SetUp() {
    NeedsClCommandQueue::SetUp();

    program = ClProgram(error, *c, "good.cl"); ASSERT_OK(error);
    // load & build program
    program.build(error, *d, ""); ASSERT_OK(error);
    cl_build_status status = program.buildStatus(error, *d); ASSERT_OK(error);
    ASSERT_EQ(CL_BUILD_SUCCESS, status) << "Build of good.cl failed.";
}

// Test getting kernel.
TEST_F(ClKernelTest, create) {
    QString name("inc");
    ClKernel kernel(error, program, name); ASSERT_OK(error);
    ASSERT_EQ(name, kernel.kernelName());
    ASSERT_NE((cl_kernel)0, kernel.get());
}

// Test getting a kernel with the wrong name.
TEST_F(ClKernelTest, badName) {
    QString vendor = p->getVendor(error); ASSERT_OK(error);
    if (vendor == "Intel(R) Corporation")
        return; // avoid bug in Intel's implementation
    ClKernel kernel(error, program, "noSuchKernel");
    ASSERT_ERR(error)
    << "Trying to get non-existent kernel should raise error.";
}

// Test querying kernel object.
TEST_F(ClKernelTest, query) {
    QString name("inc");
    ClKernel kernel(error, program, name); ASSERT_OK(error);
    QString functionName = kernel.getFunctionName(error); ASSERT_OK(error);
    EXPECT_EQ(name, functionName);
    int numArgs = kernel.getNumArgs(error); ASSERT_OK(error);
    EXPECT_EQ(1, numArgs);
}

// Test setting kernel arguments.
TEST_F(ClKernelTest, setArguments) {
    ClKernel kernel(error, program, "kernel1"); ASSERT_OK(error);

    // set buffer argument
    ClBuffer buffer(error, *c, (size_t)256); ASSERT_OK(error);
    kernel.bufferArg(error, 0, buffer); ASSERT_OK(error);

    // set local buffer argument
    kernel.localBufferArg(error, 1, (size_t)128); ASSERT_OK(error);

    // set number arguments
    kernel.charArg(  error,  2,   (qint8)10); ASSERT_OK(error);
    kernel.uCharArg( error,  3,  (quint8)11); ASSERT_OK(error);
    kernel.shortArg( error,  4,  (qint16)12); ASSERT_OK(error);
    kernel.uShortArg(error,  5, (quint16)13); ASSERT_OK(error);
    kernel.intArg(   error,  6,  (qint32)14); ASSERT_OK(error);
    kernel.uIntArg(  error,  7, (quint32)15); ASSERT_OK(error);
    kernel.longArg(  error,  8,  (qint64)16); ASSERT_OK(error);
    kernel.uLongArg( error,  9, (quint64)17); ASSERT_OK(error);
    kernel.floatArg( error, 10,      1.234f); ASSERT_OK(error);
}

// Test setting vector arguments.
TEST_F(ClKernelTest, setVectorArguments) {
    ClKernel kernel(error, program, "kernel2"); ASSERT_OK(error);

    // correct result
    const int nValues = 18;
    QVector<float> correctResult(nValues);
    for (int i = 0; i < nValues; ++i)
        correctResult[i] = (float)(i + 1);

    // output buffer
    size_t bufferSize = (size_t)nValues * sizeof(cl_float);
    ClBuffer buffer(error, *c, bufferSize, clWriteOnly); ASSERT_OK(error);
    kernel.bufferArg(error, 0, buffer); ASSERT_OK(error);

    // set vector arguments
    glm::ivec2 i2(1, 2);
    glm::ivec4 i4(3, 4, 5, 6);
    glm::uvec2 u2(7, 8);
    glm::uvec4 u4(9, 10, 11, 12);
    glm::vec2  f2(13.0f, 14.0f);
    glm::vec4  f4(15.0f, 16.0f, 17.0f, 18.0f);
    kernel.int2Arg(  error, 1, i2); ASSERT_OK(error);
    kernel.int4Arg(  error, 2, i4); ASSERT_OK(error);
    kernel.uint2Arg( error, 3, u2); ASSERT_OK(error);
    kernel.uint4Arg( error, 4, u4); ASSERT_OK(error);
    kernel.float2Arg(error, 5, f2); ASSERT_OK(error);
    kernel.float4Arg(error, 6, f4); ASSERT_OK(error);

    // run kernel
    ClTask task(kernel);
    q->enqueue(error, task); ASSERT_OK(error);

    // check result
    QVector<float> result(nValues);
    ClReadBuffer read(buffer, result.data());
    q->enqueueBlocking(error, read); ASSERT_OK(error);
    ASSERT_EQ(correctResult, result);
}

// Test querying kernel information.
TEST_F(ClKernelTest, info) {
    // (missing in ClKernel)
}

// Test querying work-group information.
TEST_F(ClKernelTest, workGroupInfo) {
    ClKernel kernel(error, program, "incTask"); ASSERT_OK(error);
    kernel.getWorkGroupSize(error, *d);         EXPECT_OK(error);
    kernel.getCompileWorkGroupSize(error, *d);  EXPECT_OK(error);
    kernel.getLocalMemSize(error, *d);          EXPECT_OK(error);
}

ClKernelTestRun::ClKernelTestRun() :
NeedsClCommandQueue(), error(), program(),
vectorSize(2), vector(vectorSize), vectorPlus1(vectorSize) {
    // initialize 'vector' with random values
    for (int i = 0; i < (int)vectorSize; ++i) {
        int n = qrand() % 256;
        vector[i] = n;
        vectorPlus1[i] = n + 1;
    }
}

ClKernelTestRun::~ClKernelTestRun() { }

void ClKernelTestRun::SetUp() {
    NeedsClCommandQueue::SetUp();

    // load & build program
    program = ClProgram(error, *c, "good.cl"); ASSERT_OK(error);
    program.build(error, *d, ""); ASSERT_OK(error);
    cl_build_status status = program.buildStatus(error, *d); ASSERT_OK(error);
    ASSERT_EQ(CL_BUILD_SUCCESS, status) << "Build of good.cl failed.";
}

// Test running kernel with NDRange.
TEST_F(ClKernelTestRun, runNDRange) {
    // set up buffer
    ClBuffer buffer(error, *c, vectorSize * sizeof(cl_int), vector.data());
    ASSERT_OK(error);

    // set up kernel
    ClKernel kernel(error, program, "inc"); ASSERT_OK(error);
    kernel.bufferArg(error, 0, buffer); ASSERT_OK(error);

    // run kernel
    ClNDRangeKernel run(kernel, ClNDRange(vectorSize));
    q->enqueue(error, run); ASSERT_OK(error);

    // check result
    QVector<int> result(vectorSize);
    ClReadBuffer read(buffer, result.data());
    q->enqueueBlocking(error, read); ASSERT_OK(error);
    ASSERT_EQ(vectorPlus1, result);
}

// Test running kernel task.
TEST_F(ClKernelTestRun, runTask) {
    // set up buffer
    ClBuffer buffer(error, *c, vectorSize * sizeof(cl_int), vector.data());
    ASSERT_OK(error);

    // set up kernel
    ClKernel kernel(error, program, "incTask"); ASSERT_OK(error);
    kernel.bufferArg(error, 0, buffer);
    kernel.intArg(error, 1, (int)vectorSize);

    // run kernel
    ClTask task(kernel);
    q->enqueue(error, task); ASSERT_OK(error);

    // check result
    QVector<int> result(vectorSize);
    ClReadBuffer read(buffer, result.data());
    q->enqueueBlocking(error, read);
    ASSERT_EQ(vectorPlus1, result);
}
