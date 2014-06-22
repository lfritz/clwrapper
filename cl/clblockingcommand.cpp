#include "clblockingcommand.h"

ClBlockingCommand::~ClBlockingCommand() { }

ClEvent ClBlockingCommand::enqueue(Error& error, const ClCommandQueue& queue,
                                   cl_uint nEvents, const cl_event * events) {
    return enqueueBlocking(error, queue, nEvents, events, false);
}
