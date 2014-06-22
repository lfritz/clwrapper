#include "cldevicetest.h"

#include <cldevice.h>
#include <clplatform.h>

#include "errorassert.h"

ClDeviceTestStatic::ClDeviceTestStatic() : error() { }
ClDeviceTestStatic::~ClDeviceTestStatic() { }

// Test ClDevice::getDevices.
TEST_F(ClDeviceTestStatic, getDevices) {
    ClDevice::getDevices(error, *p); EXPECT_OK(error);
    ClDevice::getDevices(error, *p, CL_DEVICE_TYPE_CPU); EXPECT_OK(error);
    ClDevice::getDevices(error, *p, CL_DEVICE_TYPE_GPU); EXPECT_OK(error);
    ClDevice::getDevices(error, *p, CL_DEVICE_TYPE_DEFAULT); EXPECT_OK(error);
    ClDevice::getDevices(error, *p, CL_DEVICE_TYPE_ACCELERATOR);
    EXPECT_OK(error);
}

ClDeviceTest::ClDeviceTest() : error() { }
ClDeviceTest::~ClDeviceTest() { }

// Test one-argument constructor.
TEST_F(ClDeviceTest, ctor1) {
    ClDevice d2(d->get());
    EXPECT_EQ(*d, d2);
    EXPECT_EQ(d->get(), d2.get());
}

// Test == and != operators.
TEST_F(ClDeviceTest, eq) {
    ClDevice d2(*d);
    EXPECT_TRUE(*d == d2);
    EXPECT_FALSE(*d != d2);
}

// Test functions that query a ClDevice object.
TEST_F(ClDeviceTest, basicQuery) {
    d->getType(error); EXPECT_OK(error);
    d->getVendorId(error); EXPECT_OK(error);
    d->getMaxComputeUnits(error); EXPECT_OK(error);
    d->getMaxWorkItemDimensions(error); EXPECT_OK(error);
    d->getMaxWorkItemSizes(error); EXPECT_OK(error);
    d->getMaxWorkGroupSize(error); EXPECT_OK(error);
    d->getPreferredVectorWidthChar(error); EXPECT_OK(error);
    d->getPreferredVectorWidthShort(error); EXPECT_OK(error);
    d->getPreferredVectorWidthInt(error); EXPECT_OK(error);
    d->getPreferredVectorWidthLong(error); EXPECT_OK(error);
    d->getPreferredVectorWidthFloat(error); EXPECT_OK(error);
    d->getPreferredVectorWidthChar(error); EXPECT_OK(error);
    d->getMaxClockFrequency(error); EXPECT_OK(error);
    d->getAddressBits(error); EXPECT_OK(error);
    d->getMaxMemAllocSize(error); EXPECT_OK(error);
    d->getImageSupport(error); EXPECT_OK(error);
    d->getMaxReadImageArgs(error); EXPECT_OK(error);
    d->getMaxWriteImageArgs(error); EXPECT_OK(error);
    d->getImage2DMaxWidth(error); EXPECT_OK(error);
    d->getImage2DMaxHeight(error); EXPECT_OK(error);
    d->getImage3DMaxWidth(error); EXPECT_OK(error);
    d->getImage3DMaxHeight(error); EXPECT_OK(error);
    d->getImage3DMaxDepth(error); EXPECT_OK(error);
    d->getMaxSamplers(error); EXPECT_OK(error);
    d->getMaxParameterSize(error); EXPECT_OK(error);
    d->getMemBaseAddrAlign(error); EXPECT_OK(error);
    d->getMinDataTypeAlignSize(error); EXPECT_OK(error);
    d->getSingleFpConfig(error); EXPECT_OK(error);
    d->getGlobalMemCacheType(error); EXPECT_OK(error);
    d->getGlobalMemCachelineSize(error); EXPECT_OK(error);
    d->getGlobalMemCacheSize(error); EXPECT_OK(error);
    d->getGlobalMemSize(error); EXPECT_OK(error);
    d->getMaxConstantBufferSize(error); EXPECT_OK(error);
    d->getMaxConstantArgs(error); EXPECT_OK(error);
    d->getLocalMemType(error); EXPECT_OK(error);
    d->getLocalMemSize(error); EXPECT_OK(error);
    d->getErrorCorrectionSupport(error); EXPECT_OK(error);
    d->getProfilingTimerResolution(error); EXPECT_OK(error);
    d->getEndianLittle(error); EXPECT_OK(error);
    d->getAvailable(error); EXPECT_OK(error);
    d->getCompilerAvailable(error); EXPECT_OK(error);
    d->getDeviceExecutionCapabilities(error); EXPECT_OK(error);
    d->getQueueProperties(error); EXPECT_OK(error);
    ClPlatform platform = d->getPlatform(error); EXPECT_OK(error);
    EXPECT_EQ(*p, platform);
    d->getName(error); EXPECT_OK(error);
    d->getVendor(error); EXPECT_OK(error);
    d->getDriverVersion(error); EXPECT_OK(error);
    d->getProfile(error); EXPECT_OK(error);
    d->getVersion(error); EXPECT_OK(error);
    d->getExtensions(error); EXPECT_OK(error);
}

// Test high-level querying functions.
TEST_F(ClDeviceTest, highLevelQuery) {
    d->extensionsList(error); EXPECT_OK(error);
    d->image2DMaxDimensions(error); EXPECT_OK(error);
    d->image3DMaxDimensions(error); EXPECT_OK(error);
    d->getGlobalMemSizeMB(error); EXPECT_OK(error);
    d->supportsOutOfOrderExecMode(error); EXPECT_OK(error);
    d->supportsProfiling(error); EXPECT_OK(error);
}
