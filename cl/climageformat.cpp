#include "climageformat.h"

QString channelOrderString(cl_channel_order o) {
    switch (o) {
        case CL_R:         return "CL_R";
        case CL_A:         return "CL_A";
        case CL_RG:        return "CL_RG";
        case CL_RA:        return "CL_RA";
        case CL_RGB:       return "CL_RGB";
        case CL_RGBA:      return "CL_RGBA";
        case CL_BGRA:      return "CL_BGRA";
        case CL_ARGB:      return "CL_ARGB";
        case CL_INTENSITY: return "CL_INTENSITY";
        case CL_LUMINANCE: return "CL_LUMINANCE";
    }
    return QString("unknown channel order: %1").arg(o, 0, 16);
}

QString channelTypeString(cl_channel_type t) {
    switch (t) {
        case CL_SNORM_INT8:       return "CL_SNORM_INT8";
        case CL_SNORM_INT16:      return "CL_SNORM_INT16";
        case CL_UNORM_INT8:       return "CL_UNORM_INT8";
        case CL_UNORM_INT16:      return "CL_UNORM_INT16";
        case CL_UNORM_SHORT_565:  return "CL_UNORM_SHORT_565";
        case CL_UNORM_SHORT_555:  return "CL_UNORM_SHORT_555";
        case CL_UNORM_INT_101010: return "CL_UNORM_INT_101010";
        case CL_SIGNED_INT8:      return "CL_SIGNED_INT8";
        case CL_SIGNED_INT16:     return "CL_SIGNED_INT16";
        case CL_SIGNED_INT32:     return "CL_SIGNED_INT32";
        case CL_UNSIGNED_INT8:    return "CL_UNSIGNED_INT8";
        case CL_UNSIGNED_INT16:   return "CL_UNSIGNED_INT16";
        case CL_UNSIGNED_INT32:   return "CL_UNSIGNED_INT32";
        case CL_HALF_FLOAT:       return "CL_HALF_FLOAT";
        case CL_FLOAT:            return "CL_FLOAT";
    }
    return QString("unknown channel type: %1").arg(t, 0, 16);
}

QString ClImageFormat::toString() const {
    return QString("(%1, %2)")
    .arg(channelOrderString(f.image_channel_order))
    .arg(channelTypeString(f.image_channel_data_type));
}
