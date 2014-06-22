#pragma once

// Error checking for OpenCL function calls.

#include <QString>

#include "clew.h"

class Error;

// check OpenCL status code and set error if it's not CL_SUCCESS
bool clCheckStatus(Error& error, cl_int status, const char * functionName);

// check OpenCL status code and print error message if it's not CL_SUCCESS
bool clCheckStatusPrint(cl_int status, const char * functionName);

// return a string for a status code
QString clStatusString(cl_int status);
