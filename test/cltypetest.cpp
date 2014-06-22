#include "cltypetest.h"

#include <cltype.h>
#include <gtest/gtest.h>

// Test the 'name' member variable.
TEST(ClTypeTest, name) {
    ASSERT_EQ(QString("uchar"), ClType<quint8>::name);
    ASSERT_EQ(QString("char"), ClType<qint8>::name);
}
