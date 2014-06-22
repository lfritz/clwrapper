#pragma once

#include <QtGlobal>

#include "clew.h"

class Error;

class ClEvent {
    bool isValid;
    cl_event e;

public:
    ClEvent();
    explicit ClEvent(cl_event event);

    // move and copy constructors
    ClEvent(ClEvent&& rhs);
    ClEvent(const ClEvent& rhs);

    // move and copy assignment
    ClEvent& operator=(ClEvent&& rhs);
    ClEvent& operator=(const ClEvent& rhs);

    ~ClEvent();

    cl_event get() const { return e; }
    const cl_event * pointer() const { return &e; }

    void waitFor(Error& error) const;

    // get info
    cl_command_type getCommandType(Error& error) const;
    cl_int getCommandExecutionStatus(Error& error) const;
    const char * getCommandTypeString(Error& error) const;

    // profiling data
    // the methods return -1 if profiling information is not available
    qint64 profilingCommandQueued(Error& error) const;
    qint64 profilingCommandSubmit(Error& error) const;
    qint64 profilingCommandStart(Error& error) const;
    qint64 profilingCommandEnd(Error& error) const;

    // higher-level access to profiling data
    // the methods return useless results if profiling information is not
    // available
    qint64 timeQueued(Error& error) const;
    qint64 timeSubmitted(Error& error) const;
    qint64 timeRunning(Error& error) const;
    qint64 timeLaunch(Error& error) const;

    // Check that the command completed properly; raise an error if it didn't.
    void checkStatusComplete(Error& error) const;

    // Return string with runtime. Only works if profiling is turned on.
    QString runtimeMessage(Error& error) const;

private:
    template <typename T>
    void getInfo(Error& error, cl_event_info paramName, T * value) const;
    qint64 getProfilingInfo(Error& error, cl_profiling_info paramName) const;

    void retain();
    void release();
};
