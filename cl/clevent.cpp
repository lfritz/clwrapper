#include "clevent.h"

#include "clerrorchecking.h"
#include "error.h"

ClEvent::ClEvent() : isValid(false), e(0) { }

ClEvent::ClEvent(cl_event event) : isValid(true), e(event) { }

ClEvent::ClEvent(ClEvent&& rhs) : isValid(rhs.isValid), e(rhs.e) {
    rhs.isValid = false;
}
ClEvent::ClEvent(const ClEvent& rhs) : isValid(rhs.isValid), e(rhs.e) {
    retain();
}

ClEvent& ClEvent::operator=(ClEvent&& rhs) {
    release();
    isValid = rhs.isValid;
    e = rhs.e;
    rhs.isValid = false;
    return *this;
}
ClEvent& ClEvent::operator=(const ClEvent& rhs) {
    release();
    isValid = rhs.isValid;
    e = rhs.e;
    retain();
    return *this;
}

ClEvent::~ClEvent() {
    release();
}

void ClEvent::waitFor(Error& error) const {
    cl_int status = clWaitForEvents(1, pointer());
    clCheckStatus(error, status, "clWaitForEvents");
}

cl_command_type ClEvent::getCommandType(Error& error) const {
    cl_command_type value = 0;
    getInfo<cl_command_type>(error, CL_EVENT_COMMAND_TYPE, &value);
    return value;
}

cl_int ClEvent::getCommandExecutionStatus(Error& error) const {
    cl_int value = 0;
    getInfo<cl_int>(error, CL_EVENT_COMMAND_EXECUTION_STATUS, &value);
    return value;
}

const char * ClEvent::getCommandTypeString(Error& error) const {
    cl_command_type type = getCommandType(error);
    if (error) return 0;
    switch (type) {
        case CL_COMMAND_NDRANGE_KERNEL:       return "NDRANGE_KERNEL";
        case CL_COMMAND_TASK:                 return "TASK";
        case CL_COMMAND_NATIVE_KERNEL:        return "NATIVE_KERNEL";
        case CL_COMMAND_READ_BUFFER:          return "READ_BUFFER";
        case CL_COMMAND_WRITE_BUFFER:         return "WRITE_BUFFER";
        case CL_COMMAND_COPY_BUFFER:          return "COPY_BUFFER";
        case CL_COMMAND_READ_IMAGE:           return "READ_IMAGE";
        case CL_COMMAND_WRITE_IMAGE:          return "WRITE_IMAGE";
        case CL_COMMAND_COPY_IMAGE:           return "COPY_IMAGE";
        case CL_COMMAND_COPY_BUFFER_TO_IMAGE: return "COPY_BUFFER_TO_IMAGE";
        case CL_COMMAND_COPY_IMAGE_TO_BUFFER: return "COPY_IMAGE_TO_BUFFER";
        case CL_COMMAND_MAP_BUFFER:           return "MAP_BUFFER";
        case CL_COMMAND_MAP_IMAGE:            return "MAP_IMAGE";
        case CL_COMMAND_UNMAP_MEM_OBJECT:     return "UNMAP_MEM_OBJECT";
        case CL_COMMAND_MARKER:               return "MARKER";
        case CL_COMMAND_ACQUIRE_GL_OBJECTS:   return "ACQUIRE_GL_OBJECTS";
        case CL_COMMAND_RELEASE_GL_OBJECTS:   return "RELEASE_GL_OBJECTS";
        default: return "unknown command type";
    }
}

// profiling data
qint64 ClEvent::profilingCommandQueued(Error& error) const {
    return getProfilingInfo(error, CL_PROFILING_COMMAND_QUEUED);
}
qint64 ClEvent::profilingCommandSubmit(Error& error) const {
    return getProfilingInfo(error, CL_PROFILING_COMMAND_SUBMIT);
}
qint64 ClEvent::profilingCommandStart(Error& error) const {
    return getProfilingInfo(error, CL_PROFILING_COMMAND_START);
}
qint64 ClEvent::profilingCommandEnd(Error& error) const {
    return getProfilingInfo(error, CL_PROFILING_COMMAND_END);
}

// higher-level access to profiling data
qint64 ClEvent::timeQueued(Error& error) const {
    qint64 submit = profilingCommandSubmit(error); if (error) return 0;
    qint64 queued = profilingCommandQueued(error); if (error) return 0;
    return submit - queued;
}
qint64 ClEvent::timeSubmitted(Error& error) const {
    qint64 start = profilingCommandStart(error); if (error) return 0;
    qint64 submit = profilingCommandSubmit(error); if (error) return 0;
    return start - submit;
}
qint64 ClEvent::timeRunning(Error& error) const {
    qint64 end = profilingCommandEnd(error); if (error) return 0;
    qint64 start = profilingCommandStart(error); if (error) return 0;
    return end - start;
}

qint64 ClEvent::timeLaunch(Error& error) const {
    qint64 start = profilingCommandStart(error); if (error) return 0;
    qint64 queued = profilingCommandQueued(error); if (error) return 0;
    return start - queued;
}

void ClEvent::checkStatusComplete(Error& error) const {
    cl_int executionStatus = getCommandExecutionStatus(error);
    if (error) return;
    const char * commandType = getCommandTypeString(error);
    if (error) return;
    if (executionStatus == CL_COMPLETE)
        return;

    QString msg = QString("%1 did not complete properly (%2)")
    .arg(commandType);
    switch (executionStatus) {
        case CL_QUEUED: msg = msg.arg("status is: queued"); break;
        case CL_SUBMITTED: msg = msg.arg("status is: submitted"); break;
        case CL_RUNNING: msg = msg.arg("status is: running"); break;
        default:
        if (executionStatus < 0)
            msg = msg.arg("error: %1").arg(clStatusString(executionStatus));
        else
            msg = msg.arg("unknown status: %1").arg(executionStatus);
    }
    error.set(msg);
}

QString time(qint64 ns) {
    qint64 ms = (ns + 500000) / 1000000;
    return QString("%1 ms").arg(ms, 5);
}

QString ClEvent::runtimeMessage(Error& error) const {
    qint64 r = timeRunning(error); if (error) return "";
    qint64 l = timeLaunch(error); if (error) return "";
    QString commandType(getCommandTypeString(error));
    if (error) return "";
    return QString("%1 launch time %2, run time %3")
    .arg(commandType + ":", -21).arg(time(l)).arg(time(r));
}

template <typename T>
void ClEvent::getInfo(
                      Error& error, cl_event_info paramName, T * value) const {
    cl_int status = clGetEventInfo(get(), paramName, sizeof(T), value, 0);
    clCheckStatus(error, status, "clGetEventInfo");
}

qint64 ClEvent::getProfilingInfo(Error& error,
                                 cl_profiling_info paramName) const {
    cl_ulong value = 0;
    cl_int status = clGetEventProfilingInfo(get(), paramName, sizeof(cl_ulong),
                                            &value, 0);
    if (status == CL_PROFILING_INFO_NOT_AVAILABLE)
        return -1;
    clCheckStatus(error, status, "clGetEventProfilingInfo");
    return value;
}

void ClEvent::retain() {
    if ( ! isValid) return;
    cl_int status = clRetainEvent(e);
    clCheckStatusPrint(status, "clRetainEvent");
}
void ClEvent::release() {
    if ( ! isValid) return;
    cl_int status = clReleaseEvent(e);
    clCheckStatusPrint(status, "clReleaseEvent");
}
