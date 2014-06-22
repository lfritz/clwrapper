#include "env.h"

#include <cldevice.h>
#include <cllibrary.h>
#include <clplatform.h>
#include <error.h>

#include "errorassert.h"

Env * env = 0;

Env::Env(int platformId, int deviceId) :
pid(platformId), did(deviceId),
l(0), p(0), d(0) {
    env = this;
}

Env::~Env() { }

void Env::SetUp() {
    Error error;

    // load library
    l = new ClLibrary();
    ASSERT_EQ(0, l->clewStatus()) << "could not load OpenCL library";

    // get platform
    QList<ClPlatform> platforms = l->platforms(error);
    ASSERT_OK(error);
    ASSERT_GT(platforms.size(), pid);
    p = new ClPlatform(platforms[pid]);
    QString platformName = p->getName(error); ASSERT_OK(error);
    qDebug("OpenCL platform: %s", qPrintable(platformName));

    // get device
    QList<ClDevice> devices = ClDevice::getDevices(error, *p);
    ASSERT_OK(error);
    ASSERT_GT(devices.size(), did);
    d = new ClDevice(devices[did]);
    QString deviceName = d->getName(error); ASSERT_OK(error);
    qDebug("OpenCL device: %s", qPrintable(deviceName));
}

void Env::TearDown() {
    delete d;
    delete p;
    delete l;
}
