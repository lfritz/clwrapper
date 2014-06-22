#include "clbuffertest.h"

#include <clbuffer.h>
#include <clcommandqueue.h>
#include <clcopybuffer.h>
#include <clmapbuffer.h>
#include <clreadbuffer.h>
#include <clunmapbuffer.h>
#include <clwritebuffer.h>

#include "errorassert.h"

ClBufferTestCreate::ClBufferTestCreate() : NeedsClContext(), error() { }

ClBufferTestCreate::~ClBufferTestCreate() { }

// Test creating a ClBuffer.
TEST_F(ClBufferTestCreate, create) {
    const size_t bufferSize = 1024;
    ClBuffer buffer(error, *c, bufferSize);
    size_t sizeQueried = buffer.getSize(error);
    ASSERT_OK(error);
    EXPECT_EQ(bufferSize, sizeQueried)
    << "ClBuffer::getSize returned the wrong size.";
    size_t sizeReturned = buffer.size();
    EXPECT_EQ(bufferSize, sizeReturned)
    << "ClBuffer::size returned the wrong size.";
}

ClBufferTest::ClBufferTest() :
NeedsClCommandQueue(), error(),
bufferSize(1024), input(bufferSize), output(bufferSize, 0) {
    // initialize 'input' with random values
    for (int i = 0; i < (int)bufferSize; ++i)
        input[i] = qrand() % 256;
}

ClBufferTest::~ClBufferTest() { }

// Test writing to and reading from a buffer.
TEST_F(ClBufferTest, writeAndRead) {
    ClBuffer buffer(error, *c, bufferSize); ASSERT_OK(error);
    ClWriteBuffer writeBuffer(buffer, input.constData());
    q->enqueue(error, writeBuffer); ASSERT_OK(error);
    ClReadBuffer readBuffer(buffer, output.data());
    q->enqueue(error, readBuffer); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
    EXPECT_EQ(input, output) << "Data read from buffer was not the same as "
    "data written to it.";
}

// Test initializing a buffer with CL_MEM_COPY_HOST_PTR and reading from it.
TEST_F(ClBufferTest, initAndRead) {
    ClBuffer buffer(error, *c, bufferSize, input.data(), clReadOnly);
    ASSERT_OK(error);
    ClReadBuffer readBuffer(buffer, output.data());
    q->enqueue(error, readBuffer); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
    ASSERT_EQ(input, output) << "Data read from buffer was not the same as "
    "data loaded into it.";
}

// Test copying from one buffer to another.
TEST_F(ClBufferTest, writeCopyAndRead) {
    ClBuffer in(error, *c, bufferSize, input.data(), clReadOnly);
    ASSERT_OK(error);
    ClBuffer out(error, *c, bufferSize, clWriteOnly);
    ASSERT_OK(error);
    ClCopyBuffer copyBuffer(in, out);
    q->enqueue(error, copyBuffer); ASSERT_OK(error);
    ClReadBuffer readBuffer(out, output.data());
    q->enqueue(error, readBuffer); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
    ASSERT_EQ(input, output) << "Data read from buffer was not the same as "
    "data copied into it.";
}

// Test writing to a memory-mapped buffer.
TEST_F(ClBufferTest, mapForWriting) {
    ClBuffer buffer(error, *c, bufferSize); ASSERT_OK(error);

    // memory-map and write to buffer
    ClMapBuffer mapBuffer(buffer, CL_MAP_WRITE);
    q->enqueueBlocking(error, mapBuffer); ASSERT_OK(error);
    quint8 * bytes = (quint8 * )mapBuffer.pointer();
    for (int i = 0; i < (int)bufferSize; ++i)
        bytes[i] = input[i];
    ClUnmapBuffer unmapBuffer(mapBuffer);
    q->enqueue(error, unmapBuffer); ASSERT_OK(error);

    // read data back
    ClReadBuffer readBuffer(buffer, output.data());
    q->enqueue(error, readBuffer); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);

    ASSERT_EQ(input, output) << "Data read from buffer was not the same as "
    "data written to it.";
}

// Test reading from a memory-mapped buffer.
TEST_F(ClBufferTest, mapForReading) {
    // initialize buffer with input data
    ClBuffer buffer(error, *c, bufferSize, input.data(), clReadOnly);
    ASSERT_OK(error);

    // memory-map and read data
    ClMapBuffer mapBuffer(buffer, CL_MAP_READ);
    q->enqueueBlocking(error, mapBuffer); ASSERT_OK(error);
    quint8 * bytes = (quint8 * )mapBuffer.pointer();
    for (int i = 0; i < (int)bufferSize; ++i)
        output[i] = bytes[i];
    ClUnmapBuffer unmapBuffer(mapBuffer);
    q->enqueue(error, unmapBuffer); ASSERT_OK(error);

    ASSERT_EQ(input, output) << "Data read from buffer was not the same as "
    "data loaded into it.";
}
