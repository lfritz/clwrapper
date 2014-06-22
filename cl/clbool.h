#pragma once

// Functions to convert from cl_bool to bool and back.

inline bool toBool(cl_bool b) { return b != CL_FALSE; }
inline cl_bool clBool(bool b) { return b ? CL_TRUE : CL_FALSE; }
