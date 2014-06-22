#include "clcommandqueue.h"

#include "clblockingcommand.h"
#include "clcommand.h"
#include "clcontext.h"
#include "cldevice.h"
#include "clerrorchecking.h"
#include "error.h"

ClCommandQueue::ClCommandQueue() : isValid(false), q(0) { }

ClCommandQueue::ClCommandQueue(Error& error, const ClContext& context,
                               const ClDevice& device, bool outOfOrderExecMode,
                               bool profiling)
: isValid(false), q(0) {
    // if out-of-order exec mode is not supported, turn it off
    if (outOfOrderExecMode) {
        outOfOrderExecMode &= device.supportsOutOfOrderExecMode(error);
        if (error) return;
    }

    cl_command_queue_properties properties = 0;
    if (outOfOrderExecMode)
        properties |= CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE;
    if (profiling)
        properties |= CL_QUEUE_PROFILING_ENABLE;

    cl_int status = CL_SUCCESS;
    q = clCreateCommandQueue(context.get(), device.get(), properties, &status);
    if (status == CL_SUCCESS)
        isValid = true;
    else
        clCheckStatus(error, status, "clCreateCommandQueue");
}

ClCommandQueue::ClCommandQueue(ClCommandQueue&& rhs)
: isValid(rhs.isValid), q(rhs.q) {
    rhs.isValid = false;
}
ClCommandQueue::ClCommandQueue(const ClCommandQueue& rhs)
: isValid(rhs.isValid), q(rhs.q) {
    retain();
}

ClCommandQueue& ClCommandQueue::operator=(ClCommandQueue&& rhs) {
    release();
    isValid = rhs.isValid;
    q = rhs.q;
    rhs.isValid = false;
    return *this;
}
ClCommandQueue& ClCommandQueue::operator=(const ClCommandQueue& rhs) {
    release();
    isValid = rhs.isValid;
    q = rhs.q;
    retain();
    return *this;
}

ClCommandQueue::~ClCommandQueue() {
    release();
}

ClDevice ClCommandQueue::getDevice(Error& error) const {
    cl_device_id deviceId = 0;
    getInfo(error, CL_QUEUE_DEVICE, deviceId);
    if (error) return ClDevice();
    return ClDevice(deviceId);
}

bool ClCommandQueue::getOutOfOrderExecMode(Error& error) const {
    return getProperty(error, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE);
}

bool ClCommandQueue::getProfiling(Error& error) const {
    return getProperty(error, CL_QUEUE_PROFILING_ENABLE);
}

ClEvent ClCommandQueue::enqueue(Error& error, ClCommand& c) const {
    return c.enqueue(error, *this, 0, 0);
}
ClEvent ClCommandQueue::enqueue(Error& error, ClCommand& c,
        const ClEvent& waitFor) const {
    return c.enqueue(error, *this, 1, waitFor.pointer());
}
ClEvent ClCommandQueue::enqueue(Error& error, ClCommand& c,
        const ClEventList& waitFor) const {
    QVector<cl_event> vec = eventVector(waitFor);
    return c.enqueue(error, *this, vec.size(), vec.data());
}

ClEvent ClCommandQueue::enqueueBlocking(Error& error,
                                        ClBlockingCommand& c) const {
    return c.enqueueBlocking(error, *this, 0, 0, true);
}
ClEvent ClCommandQueue::enqueueBlocking(Error& error, ClBlockingCommand& c,
                                        const ClEvent& waitFor) const {
    return c.enqueueBlocking(error, *this, 1, waitFor.pointer(), true);
}
ClEvent ClCommandQueue::enqueueBlocking(Error& error, ClBlockingCommand& c,
                                        const ClEventList& waitFor) const {
    QVector<cl_event> vec = eventVector(waitFor);
    return c.enqueueBlocking(error, *this, vec.size(), vec.data(), true);
}

void ClCommandQueue::enqueueBarrier(Error& error) const {
    cl_int status = clEnqueueBarrier(q);
    clCheckStatus(error, status, "clEnqueueBarrier");
}

ClEvent ClCommandQueue::enqueueMarker(Error& error) const {
    cl_event e = 0;
    cl_int status = clEnqueueMarker(q, &e);
    clCheckStatus(error, status, "clEnqueueMarker");
    return ClEvent(e);
}

void ClCommandQueue::enqueueWaitFor(Error& error,
                                    const ClEvent& waitFor) const {
    cl_int status = clEnqueueWaitForEvents(q, 1, waitFor.pointer());
    clCheckStatus(error, status, "clEnqueueWaitForEvents");
}

void ClCommandQueue::enqueueWaitFor(Error& error,
                                    const ClEventList& waitFor) const {
    QVector<cl_event> vec = eventVector(waitFor);
    cl_int status = clEnqueueWaitForEvents(q, vec.size(), vec.data());
    clCheckStatus(error, status, "clEnqueueWaitForEvents");
}

void ClCommandQueue::flush(Error& error) const {
    cl_int status = clFlush(q);
    clCheckStatus(error, status, "clFlush");
}

void ClCommandQueue::finish(Error& error) const {
    cl_int status = clFinish(q);
    clCheckStatus(error, status, "clFinish");
}

bool ClCommandQueue::getProperty(Error& error,
        cl_command_queue_properties property) const {
    cl_command_queue_properties properties;
    getInfo(error, CL_QUEUE_PROPERTIES, properties);
    if (error) return false;
    return properties & property;
}

template <typename T>
void ClCommandQueue::getInfo(Error& error,
                             cl_command_queue_info paramName,
                             T& value) const {
    cl_int status = clGetCommandQueueInfo(q, paramName, sizeof(T), &value, 0);
    clCheckStatus(error, status, "clGetCommandQueueInfo");
}

void ClCommandQueue::retain() {
    if ( ! isValid) return;
    cl_int status = clRetainCommandQueue(q);
    clCheckStatusPrint(status, "clRetainCommandQueue");
}
void ClCommandQueue::release() {
    if ( ! isValid) return;
    cl_int status = clReleaseCommandQueue(q);
    clCheckStatusPrint(status, "clReleaseCommandQueue");
}
