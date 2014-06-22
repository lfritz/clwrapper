#include "clndrange.h"

ClNDRange::ClNDRange(size_t dim0, size_t dim1, size_t dim2) :
dim(3),
asString(QString("%1x%2x%3").arg(dim0).arg(dim1).arg(dim2)) {
    values[0] = dim0;
    values[1] = dim1;
    values[2] = dim2;
}

ClNDRange::ClNDRange(size_t dim0, size_t dim1) :
dim(2),
asString(QString("%1x%2").arg(dim0).arg(dim1)) {
    values[0] = dim0;
    values[1] = dim1;
}

ClNDRange::ClNDRange(size_t dim0) :
dim(1),
asString(QString((int)dim0)) {
    values[0] = dim0;
}
