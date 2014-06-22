#include "cleventtest.h"

#include <clbuffer.h>
#include <clcommandqueue.h>
#include <clevent.h>
#include <clwritebuffer.h>

#include "errorassert.h"

ClEventTest::ClEventTest() : NeedsClCommandQueue(), error() { }

ClEventTest::~ClEventTest() { }

// Test querying the event objevt for a simple "write buffer" command.
TEST_F(ClEventTest, query) {
    // create buffer
    ClBuffer buffer(error, *c, (size_t)1);

    // enqueue and wait for buffer write command
    quint8 data = 42;
    ClWriteBuffer write(buffer, &data);
    ClEvent e = q->enqueue(error, write); ASSERT_OK(error);
    e.waitFor(error); ASSERT_OK(error);

    // query event object
    cl_command_type commandType = e.getCommandType(error); ASSERT_OK(error);
    cl_int status = e.getCommandExecutionStatus(error); ASSERT_OK(error);
    const char * typeStr = e.getCommandTypeString(error); ASSERT_OK(error);
    e.profilingCommandQueued(error); ASSERT_OK(error);
    e.profilingCommandSubmit(error); ASSERT_OK(error);
    e.profilingCommandStart(error); ASSERT_OK(error);
    e.profilingCommandEnd(error); ASSERT_OK(error);
    e.timeQueued(error); ASSERT_OK(error);
    e.timeSubmitted(error); ASSERT_OK(error);
    e.timeRunning(error); ASSERT_OK(error);
    ASSERT_EQ((cl_command_type)CL_COMMAND_WRITE_BUFFER, commandType);
    ASSERT_EQ(CL_COMPLETE, status);
    ASSERT_TRUE(typeStr);

    // misc functions
    e.checkStatusComplete(error); ASSERT_OK(error);
    e.runtimeMessage(error); ASSERT_OK(error);
}
