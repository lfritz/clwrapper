#include "cltype.h"

const QString ClType<quint8>::name("uchar");
const QString ClType<quint8>::readImageFunction("read_imageui");
const QString ClType<quint8>::writeImageFunction("write_imageui");

const QString ClType<qint8>::name("char");
const QString ClType<qint8>::readImageFunction("read_imagei");
const QString ClType<qint8>::writeImageFunction("write_imagei");

const QString ClType<quint16>::name("ushort");
const QString ClType<quint16>::readImageFunction("read_imageui");
const QString ClType<quint16>::writeImageFunction("write_imageui");

const QString ClType<qint16>::name("short");
const QString ClType<qint16>::readImageFunction("read_imagei");
const QString ClType<qint16>::writeImageFunction("write_imagei");

const QString ClType<quint32>::name("uint");
const QString ClType<quint32>::readImageFunction("read_imageui");
const QString ClType<quint32>::writeImageFunction("write_imageui");

const QString ClType<qint32>::name("int");
const QString ClType<qint32>::readImageFunction("read_imagei");
const QString ClType<qint32>::writeImageFunction("write_imagei");

const QString ClType<quint64>::name("ulong");

const QString ClType<qint64>::name("long");

const QString ClType<float>::name("float");
const QString ClType<float>::readImageFunction("read_imagef");
const QString ClType<float>::writeImageFunction("write_imagef");
