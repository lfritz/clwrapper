#pragma once

#include <QByteArray>
#include <QList>
#include <QPair>
#include <QString>

#include "clew.h"

class ClContext;
class ClDevice;
class Error;

// Wrapper class for OpenCL program objects.
class ClProgram {
    bool isValid;
    cl_program p;

public:
    ClProgram();

    // move and copy constructors
    ClProgram(ClProgram&& rhs);
    ClProgram(const ClProgram& rhs);

    // move and copy assignment
    ClProgram& operator=(ClProgram&& rhs);
    ClProgram& operator=(const ClProgram& rhs);

    ~ClProgram();

    // Load source code from file or resource and create program.
    ClProgram(Error& error, const ClContext& context, QString name);

    // Create program from binary.
    ClProgram(Error& error, const ClContext& context, const ClDevice& device,
              QByteArray bytes);

    // Create program from binaries.
    ClProgram(Error& error, const ClContext& context,
              QList< QPair<ClDevice, QByteArray> > pairs);

    cl_program get() const { return p; }

    void build(Error& error, const ClDevice& device, const char * options);
    void build(Error& error, QList<ClDevice> devices, const char * options);

    cl_build_status buildStatus(Error& error, const ClDevice& device);
    QString buildStatusString(Error& error, const ClDevice& device);
    QString buildOptions(Error& error, const ClDevice& device);
    QString buildLog(Error& error, const ClDevice& device);

    // return the program binary for the given device
    QByteArray getBinary(Error& error, const ClDevice& device);

    // misssing: get devices
    // misssing: get program source

private:
    template <typename T>
    void getInfo(Error& error, cl_program_info paramName,
                 T * value) const;
    void getInfoArray(Error& error, cl_program_info paramName,
                      void * data, size_t size) const;
    QString buildInfo(Error& error, cl_program_build_info paramName,
                      const ClDevice& device);

    void retain();
    void release();
};
