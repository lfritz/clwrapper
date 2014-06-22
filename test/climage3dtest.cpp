#include "climage3dtest.h"

#include <clbuffer.h>
#include <clcommandqueue.h>
#include <clcopybuffertoimage.h>
#include <clcopyimage.h>
#include <clcopyimagetobuffer.h>
#include <climage3d.h>
#include <clmapimage.h>
#include <clreadbuffer.h>
#include <clreadimage.h>
#include <clunmapimage.h>
#include <clwriteimage.h>
#include <glm/glm.hpp>

#include "errorassert.h"

using glm::ivec3;

ClImage3DTestStatic::ClImage3DTestStatic() : NeedsClContext(), error() { }

ClImage3DTestStatic::~ClImage3DTestStatic() { }

// Test creating a ClImage3D.
TEST_F(ClImage3DTestStatic, create) {
    ClImageFormat format(CL_RGBA, CL_SIGNED_INT32);
    ivec3 dim(8, 16, 32);
    ClImage3D im(error, *c, format, dim); ASSERT_OK(error);

    ClImageFormat formatReturned = im.getFormat(error); ASSERT_OK(error);
    ASSERT_EQ(format, formatReturned);
    ASSERT_EQ(dim, im.dimensions());
    ASSERT_EQ(dim.x, im.width());
    ASSERT_EQ(dim.y, im.height());
    ASSERT_EQ(dim.z, im.depth());
}

// Test ClImage3D::supportedFormats.
TEST_F(ClImage3DTestStatic, supportedFormats) {
    QVector<ClImageFormat> formats = ClImage3D::supportedFormats(error, *c);
    ASSERT_OK(error);

    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_UNORM_INT8)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_UNORM_INT16)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_SIGNED_INT8)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_SIGNED_INT16)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_SIGNED_INT32)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_UNSIGNED_INT8)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_UNSIGNED_INT16)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_UNSIGNED_INT32)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_HALF_FLOAT)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_RGBA, CL_FLOAT)));
    ASSERT_TRUE(formats.contains(ClImageFormat(CL_BGRA, CL_UNORM_INT8)));
}

ClImage3DTest::ClImage3DTest() :
NeedsClCommandQueue(), error(),
format(CL_RGBA, CL_SIGNED_INT32), dim(8, 16, 32),
bufferSize(4 * dim.x * dim.y * dim.z * sizeof(cl_int)),
vectorSize(4 * dim.x * dim.y * dim.z),
input(vectorSize), output(vectorSize, 0) {
    // initialize 'input' with random values
    for (int i = 0; i < (int)vectorSize; ++i)
        input[i] = qrand();
}

ClImage3DTest::~ClImage3DTest() { }

// Test writing to and reading from an image.
TEST_F(ClImage3DTest, writeAndRead) {
    ClImage3D im(error, *c, format, dim); ASSERT_OK(error);
    ClWriteImage write(im, input.data());
    q->enqueue(error, write); ASSERT_OK(error);
    ClReadImage read(im, output.data());
    q->enqueue(error, read); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
    ASSERT_EQ(input, output) << "Data read from image was not the same as "
    "data written to it.";
}

// Test initializing an image with CL_MEM_COPY_HOST_PTR and reading from it.
TEST_F(ClImage3DTest, initAndRead) {
    ClImage3D im(error, *c, format, dim, input.data(), 0,0, clReadOnly);
    ASSERT_OK(error);
    ClReadImage read(im, output.data());
    q->enqueue(error, read); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
    ASSERT_EQ(input, output) << "Data read from image was not the same as "
    "data loaded into it.";
}

// Test copying from an image to another image.
TEST_F(ClImage3DTest, copy) {
    ClImage3D in(error, *c, format, dim, input.data(), 0,0, clReadOnly);
    ASSERT_OK(error);
    ClImage3D out(error, *c, format, dim);
    ASSERT_OK(error);
    ClCopyImage copy(in, out);
    q->enqueue(error, copy); ASSERT_OK(error);
    ClReadImage read(out, output.data());
    q->enqueue(error, read); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
    ASSERT_EQ(input, output) << "Data read from image was not the same as "
    "data copied to it.";
}

// Test copying from an image to a buffer.
TEST_F(ClImage3DTest, copyImageToBuffer) {
    ClImage3D in(error, *c, format, dim, input.data(), 0,0, clReadOnly);
    ASSERT_OK(error);
    ClBuffer out(error, *c, bufferSize);
    ASSERT_OK(error);
    ClCopyImageToBuffer copy(in, out);
    q->enqueue(error, copy); ASSERT_OK(error);
    ClReadBuffer read(out, output.data());
    q->enqueue(error, read); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
    ASSERT_EQ(input, output) << "Data read from buffer was not the same as "
    "data copied to it.";
}

// Test copying from a buffer to an image.
TEST_F(ClImage3DTest, copyBufferToImage) {
    ClBuffer in(error, *c, bufferSize, input.data(), clReadOnly);
    ASSERT_OK(error);
    ClImage3D out(error, *c, format, dim);
    ASSERT_OK(error);
    ClCopyBufferToImage copy(in, out);
    q->enqueue(error, copy); ASSERT_OK(error);
    ClReadImage read(out, output.data());
    q->enqueue(error, read); ASSERT_OK(error);
    q->finish(error); ASSERT_OK(error);
    ASSERT_EQ(input, output) << "Data read from image was not the same as "
    "data copied to it.";
}

// Test reading a memory-mapped image.
TEST_F(ClImage3DTest, map) {
    // initialize image with input data
    ClImage3D im(error, *c, format, dim, input.data(), 0,0, clReadOnly);
    ASSERT_OK(error);

    // memory-map and read data
    ClMapImage map(im, CL_MAP_READ);
    q->enqueueBlocking(error, map); ASSERT_OK(error);
    quint8 * mapped = (quint8 * )map.pointer();
    size_t rowPitch = map.imageRowPitch();
    size_t slicePitch = map.imageSlicePitch();
    int rowLength = 4 * (int)dim.x;
    int sliceLength = 4 * (int)dim.y * (int)dim.x;
    for (int z = 0; z < (int)dim.z; ++z) {
        for (int y = 0; y < (int)dim.y; ++y) {
            qint32 * row = (qint32 * )(&mapped[z*slicePitch + y*rowPitch]);
            for (int x = 0; x < rowLength; ++x)
                output[z*sliceLength + y*rowLength + x] = row[x];
        }
    }
    ClUnmapImage unmap(map);
    q->enqueue(error, unmap); ASSERT_OK(error);

    ASSERT_EQ(input, output) << "Data read from image was not the same as "
    "data loaded into it.";
}
