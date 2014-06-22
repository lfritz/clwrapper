#include "needsclcontext.h"

#include <clcontext.h>
#include <error.h>

#include "errorassert.h"

NeedsClContext::NeedsClContext() : NeedsClDevice(), c(0) { }

NeedsClContext::~NeedsClContext() { }

void NeedsClContext::SetUp() {
    Error error;
    ClContext context(error, *p, *d); ASSERT_OK(error);
    c = new ClContext(context);
}
