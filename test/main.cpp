#include <QString>
#include <gtest/gtest.h>

#include "env.h"

int main(int argc, char ** argv) {
    // parse command-line arguments
    int platformId = 0;
    int deviceId = 0;
    bool ok = false;
    int i = 0;
    while (++i < argc) {
        int n = QString(argv[i]).toInt(&ok);
        if (ok) {
            platformId = n;
            break;
        }
    }
    while (++i < argc) {
        int n = QString(argv[i]).toInt(&ok);
        if (ok) {
            deviceId = n;
            break;
        }
    }

    // set up environment
    testing::AddGlobalTestEnvironment(new Env(platformId, deviceId));

    // run tests
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
