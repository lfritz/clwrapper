#pragma once

#include <QString>
#include <QtGlobal>

#include "clew.h"

template<typename T>
struct ClType {
};

template<>
struct ClType<quint8> {
    static const QString name;
    static const cl_channel_type imageChannelType = CL_UNSIGNED_INT8;
    static const QString readImageFunction;
    static const QString writeImageFunction;
};

template<>
struct ClType<qint8> {
    static const QString name;
    static const cl_channel_type imageChannelType = CL_SIGNED_INT8;
    static const QString readImageFunction;
    static const QString writeImageFunction;
};

template<>
struct ClType<quint16> {
    static const QString name;
    static const cl_channel_type imageChannelType = CL_UNSIGNED_INT16;
    static const QString readImageFunction;
    static const QString writeImageFunction;
};

template<>
struct ClType<qint16> {
    static const QString name;
    static const cl_channel_type imageChannelType = CL_SIGNED_INT16;
    static const QString readImageFunction;
    static const QString writeImageFunction;
};

template<>
struct ClType<quint32> {
    static const QString name;
    static const cl_channel_type imageChannelType = CL_UNSIGNED_INT32;
    static const QString readImageFunction;
    static const QString writeImageFunction;
};

template<>
struct ClType<qint32> {
    static const QString name;
    static const cl_channel_type imageChannelType = CL_SIGNED_INT32;
    static const QString readImageFunction;
    static const QString writeImageFunction;
};

template<>
struct ClType<quint64> {
    static const QString name;
    // no image channel types for 64-bit components
};

template<>
struct ClType<qint64> {
    static const QString name;
    // no image channel types for 64-bit components
};

template<>
struct ClType<float> {
    static const QString name;
    static const cl_channel_type imageChannelType = CL_FLOAT;
    static const QString readImageFunction;
    static const QString writeImageFunction;
};
