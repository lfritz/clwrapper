#include "clunmapimage.h"

#include "clcommandqueue.h"
#include "clerrorchecking.h"
#include "climage.h"
#include "clmapimage.h"

ClUnmapImage::ClUnmapImage(const ClImage& i, void * mappedPointer) :
mem(i), ptr(mappedPointer) { }

ClUnmapImage::ClUnmapImage(const ClMapImage& mapImage) :
mem(mapImage.memObject()), ptr(mapImage.pointer()) { }

ClEvent ClUnmapImage::enqueue(Error& error, const ClCommandQueue& queue,
                              cl_uint nEvents, const cl_event * events) {
    cl_event e = 0;
    cl_int status = clEnqueueUnmapMemObject(queue.get(), mem.get(), ptr,
                                            nEvents, events, &e);
    clCheckStatus(error, status, "clEnqueueUnmapMemObject");
    return ClEvent(e);
}
