#pragma once

#include <QString>
#include <QStringList>

#include "clew.h"

class Error;

// Wrapper class for OpenCL platforms.
class ClPlatform {
    cl_platform_id id;

public:
    ClPlatform();
    ClPlatform(cl_platform_id platformId);
    cl_platform_id get() const { return id; }
    bool operator==(const ClPlatform& other) const { return id == other.id; }
    bool operator!=(const ClPlatform& other) const { return id != other.id; }

    // get platform info
    QString getProfile(Error& error) const;
    QString getVersion(Error& error) const;
    QString getName(Error& error) const;
    QString getVendor(Error& error) const;
    QString getExtensions(Error& error) const;

    QStringList extensionsList(Error& error) const;

private:
    QString getStringInfo(Error& error, cl_device_info paramName) const;
};
