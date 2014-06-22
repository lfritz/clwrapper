__kernel void k(
    __global int * dst,
    __constant int * src) {

    if (dst[0] == 0)
        dst[0] = 1;

    dst[0] = src[0];
}
