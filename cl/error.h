#pragma once

#include <QString>

// Very simple error handling.
//
// The idea is to pass a reference (or pointer) to an Error object in any
// function call that might result in an error, then use code like this:
//     if (error) { ... }
// to check for and handle errors.
class Error {
    bool error;
    QString msg;

public:
    Error() : error(false), msg() { }
    explicit Error(const Error& e) { error = e.error; msg = e.msg; }

    // signal an error
    void set(QString m) { error = true; msg = m; }

    // convert to bool to check for error
    operator bool() const { return error; }

    void clear() { error = false; }

    // the error message (only call this if error() returns true)
    QString what() const { return msg; }
};
