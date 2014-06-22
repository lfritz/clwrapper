#pragma once

#include "clcommand.h"

class ClImage;
class ClMapImage;
class ClMem;

class ClUnmapImage : public ClCommand {
    const ClMem& mem;
    void * ptr;

public:
    ClUnmapImage(const ClImage& i, void * mappedPointer);
    ClUnmapImage(const ClMapImage& mapImage);

    ClEvent enqueue(Error& error, const ClCommandQueue& queue,
                    cl_uint nEvents, const cl_event * events);
};
