#include "needsclcommandqueue.h"

#include <clcommandqueue.h>
#include <error.h>

#include "errorassert.h"

NeedsClCommandQueue::NeedsClCommandQueue() : NeedsClContext(), q(0) { }

NeedsClCommandQueue::~NeedsClCommandQueue() { }

void NeedsClCommandQueue::SetUp() {
    NeedsClContext::SetUp();

    Error error;
    ClCommandQueue queue(error, *c, *d, false, false); ASSERT_OK(error);
    q = new ClCommandQueue(queue);
}
