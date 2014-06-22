#include "errorassert.h"

#include <error.h>

testing::AssertionResult assertOK(const char *, Error& error) {
    if (error) {
        QString msg = error.what();
        error.clear();
        return testing::AssertionFailure() << "Error: " << qPrintable(msg);
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult assertErr(const char *, Error& error) {
    if (error) {
        error.clear();
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "Expected error.";
}
