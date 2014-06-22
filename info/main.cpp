#include <QDebug>
#include <QList>
#include <QString>
#include <QStringList>
#include <cldevice.h>
#include <cllibrary.h>
#include <clplatform.h>
#include <error.h>

const char * yesNo(bool b) {
    return b ? "yes" : "no";
}

void checkError(const Error& error) {
    if (error) {
        qDebug("Error: %s", qPrintable(error.what()));
        exit(1);
    }
}

void deviceInfo(Error& error, const ClDevice& device) {
    QString name      = device.getName(error);               checkError(error);
    QString version   = device.getVersion(error);            checkError(error);
    int computeUnits  = device.getMaxComputeUnits(error);    checkError(error);
    int mem           = device.getGlobalMemSizeMB(error);    checkError(error);
    long int maxAlloc = device.getMaxMemAllocSize(error);    checkError(error);
    int maxAllocMB    = maxAlloc / 1024 / 1024;
    bool ooo     = device.supportsOutOfOrderExecMode(error); checkError(error);
    QStringList ext   = device.extensionsList(error);        checkError(error);
    bool imageSupport = device.getImageSupport(error);       checkError(error);
    size_t maxw2D     = device.getImage2DMaxWidth(error);    checkError(error);
    size_t maxh2D     = device.getImage2DMaxHeight(error);   checkError(error);
    size_t maxw3D     = device.getImage3DMaxWidth(error);    checkError(error);
    size_t maxh3D     = device.getImage3DMaxHeight(error);   checkError(error);
    size_t maxd3D     = device.getImage3DMaxDepth(error);    checkError(error);
    size_t maxWGSize  = device.getMaxWorkGroupSize(error);   checkError(error);
    qDebug("    * %s", qPrintable(name));
    qDebug("      OpenCL version: %s", qPrintable(version));
    qDebug("      Compute units: %d", computeUnits);
    qDebug("      Memory: %d MiB", mem);
    qDebug("      Maximum memory allocation size: %d MiB", maxAllocMB);
    qDebug("      Out-of-order exec mode? %s", yesNo(ooo));
    qDebug("      Double-precision support? %s",
            yesNo(ext.contains("cl_khr_fp64")));
    qDebug("      Image support? %s", yesNo(imageSupport));
    if (imageSupport) {
        qDebug("      Max size for 2D images: %lux%lu", maxw2D, maxh2D);
        qDebug("      Max size for 3D images: %lux%lux%lu",
                maxw3D, maxh3D, maxd3D);
        qDebug("      Max work-group size: %d", (int)maxWGSize);
        qDebug("      cl_khr_3d_image_writes? %s",
                yesNo(ext.contains("cl_khr_3d_image_writes")));
    }
}

int main(int, char **) {
    Error error;

    ClLibrary library;
    if (library.clewStatus()) {
        qDebug("Error loading OpenCL library (%s)", library.filename());
        return 1;
    }

    QList<ClPlatform> platforms = library.platforms(error);
    checkError(error);

    qDebug("OpenCL platforms:");
    foreach (const ClPlatform& platform, platforms) {
        QString name    = platform.getName(error);        checkError(error);
        QString version = platform.getVersion(error);     checkError(error);
        QStringList ext = platform.extensionsList(error); checkError(error);
        qDebug(" * %s", qPrintable(name));
        qDebug("   OpenCL version: %s", qPrintable(version));
        qDebug("   Devices:");
        QList<ClDevice> devices = ClDevice::getDevices(error, platform);
        foreach (const ClDevice& device, devices)
            deviceInfo(error, device);
    }

    return 0;
}
