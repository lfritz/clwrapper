#include "clcontexttest.h"

#include <clcontext.h>
#include <cldevice.h>

#include "errorassert.h"

ClContextTest::ClContextTest() : error() { }

ClContextTest::~ClContextTest() { }

// Test ClContextTest::getDevices.
TEST_F(ClContextTest, getDevices) {
    QList<ClDevice> devices = c->getDevices(error);
    ASSERT_OK(error);
    ASSERT_EQ(1, devices.size())
    << "ClDevice::getDevices should have returned one device.";
    ClDevice device = devices[0];
    ASSERT_EQ(*d, device) << "Device returned by ClContext::getDevices "
    "should be the one used when creating the context.";
}
