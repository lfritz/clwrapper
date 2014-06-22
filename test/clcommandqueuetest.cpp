#include "clcommandqueuetest.h"

#include <clcommandqueue.h>
#include <cldevice.h>

#include "errorassert.h"

ClCommandQueueTest::ClCommandQueueTest() : error() { }

ClCommandQueueTest::~ClCommandQueueTest() { }

// Test querying ClCommandQueue object.
TEST_F(ClCommandQueueTest, query) {
    ClDevice device = q->getDevice(error);
    ASSERT_OK(error);
    ASSERT_EQ(*d, device) << "Device returned by ClCommandQueue::getDevice "
    "should be the one used when creating the queue.";
    bool ooo = q->getOutOfOrderExecMode(error);
    ASSERT_OK(error);
    ASSERT_FALSE(ooo) << "Out-of-order exec mode was not enabled.";
    bool profiling = q->getProfiling(error);
    ASSERT_OK(error);
    ASSERT_FALSE(profiling) << "Profiling was not enabled.";
}

// Test misc functions.
TEST_F(ClCommandQueueTest, misc) {
    q->enqueueBarrier(error); ASSERT_OK(error);
    q->enqueueMarker(error); ASSERT_OK(error);
    q->flush(error); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
}
