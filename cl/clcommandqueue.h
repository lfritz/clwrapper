#pragma once

#include "clevent.h"
#include "cleventlist.h"
#include "clew.h"

class ClBlockingCommand;
class ClCommand;
class ClContext;
class ClDevice;
class Error;

// Wrapper class for OpenCL command queue objects.
//
// There's no method for clSetCommandQueueProperty, because that function is
// removed in OpenCL 1.1.
class ClCommandQueue {
    bool isValid;
    cl_command_queue q;

public:
    ClCommandQueue();
    ClCommandQueue(Error& error, const ClContext& context,
                   const ClDevice& device, bool outOfOrderExecMode,
                   bool profiling);

    // move and copy constructors
    ClCommandQueue(ClCommandQueue&& rhs);
    ClCommandQueue(const ClCommandQueue& rhs);

    // move and copy assignment
    ClCommandQueue& operator=(ClCommandQueue&& rhs);
    ClCommandQueue& operator=(const ClCommandQueue& rhs);

    ~ClCommandQueue();

    cl_command_queue get() const { return q; }

    // get command queue info
    ClDevice getDevice(Error& error) const;
    bool getOutOfOrderExecMode(Error& error) const;
    bool getProfiling(Error& error) const;

    // missing: get context

    ClEvent enqueue(Error& error, ClCommand& c) const;
    ClEvent enqueue(Error& error, ClCommand& c, const ClEvent& waitFor) const;
    ClEvent enqueue(Error& error, ClCommand& c,
            const ClEventList& waitFor) const;

    ClEvent enqueueBlocking(Error& error, ClBlockingCommand& c) const;
    ClEvent enqueueBlocking(Error& error, ClBlockingCommand& c,
            const ClEvent& waitFor) const;
    ClEvent enqueueBlocking(Error& error, ClBlockingCommand& c,
            const ClEventList& waitFor) const;

    // missing: enqueue native kernel

    void enqueueBarrier(Error& error) const;

    ClEvent enqueueMarker(Error& error) const;

    void enqueueWaitFor(Error& error, const ClEvent& waitFor) const;
    void enqueueWaitFor(Error& error, const ClEventList& waitFor) const;

    void flush(Error& error) const;
    void finish(Error& error) const;

private:
    bool getProperty(Error& error, cl_command_queue_properties property) const;
    template <typename T>
        void getInfo(Error& error,
                cl_command_queue_info paramName, T& value) const;

    void retain();
    void release();
};
