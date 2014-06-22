#pragma once

#include <QString>

#include "clew.h"

// Wrapper class for cl_image_format structure.
class ClImageFormat {
    cl_image_format f;

public:
    ClImageFormat() : f() { }
    ClImageFormat(cl_image_format ff) : f(ff) { }
    ClImageFormat(cl_channel_order o, cl_channel_type t) : f() {
        f.image_channel_order = o;
        f.image_channel_data_type = t;
    }

    cl_channel_order channelOrder() const { return f.image_channel_order; }
    cl_channel_type channelType() const { return f.image_channel_data_type; }

    operator cl_image_format() const { return f; }
    const cl_image_format * pointer() const { return &f; }

    bool operator==(const ClImageFormat& other) const {
        return other.f.image_channel_order == f.image_channel_order
        && other.f.image_channel_data_type == f.image_channel_data_type;
    }

    QString toString() const;
};
