#include "clplatformtest.h"

#include <cllibrary.h>
#include <clplatform.h>

#include "env.h"
#include "errorassert.h"

// Test ClPlatform::platforms.
TEST(ClPlatformTestStatic, platforms) {
    Error error;
    env->library()->platforms(error);
    ASSERT_OK(error);
}

ClPlatformTest::ClPlatformTest() : error() { }
ClPlatformTest::~ClPlatformTest() { }

// Test == and != operators.
TEST_F(ClPlatformTest, eq) {
    ClPlatform p2(*p);
    EXPECT_TRUE(*p == p2);
    EXPECT_FALSE(*p != p2);
}

// Test querying a ClPlatform object.
TEST_F(ClPlatformTest, query) {
    p->getProfile(error);     EXPECT_OK(error);
    p->getVersion(error);     EXPECT_OK(error);
    p->getName(error);        EXPECT_OK(error);
    p->getVendor(error);      EXPECT_OK(error);
    p->getExtensions(error);  EXPECT_OK(error);
    p->extensionsList(error); EXPECT_OK(error);
}
