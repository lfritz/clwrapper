__kernel void inc(__global int *vector) {
    size_t i = get_global_id(0);
    vector[i] = vector[i] + 1;
}

__kernel void incTask(__global int *vector, int size) {
    for (int i = 0; i < size; i++)
        vector[i] = vector[i] + 1;
}

__kernel void kernel1(__global float *output, __local float *temp,
    char c, uchar uc, short s, ushort us, int i, uint ui,
    long l, ulong ul, float f) {
    if (i > 5)
        temp[0] = (float)c + (float)uc + (float)s + (float)us;
    else
        temp[0] = (float)ui + (float)l + (float)ul;
    output[0] = temp[0] + f;
}

__kernel void kernel2(
    __global float *output,
    int2 i2, int4 i4,
    uint2 u2, uint4 u4,
    float2 f2, float4 f4) {
    output[0] = (float)i2.x;
    output[1] = (float)i2.y;

    output[2] = (float)i4.x;
    output[3] = (float)i4.y;
    output[4] = (float)i4.z;
    output[5] = (float)i4.w;

    output[6] = (float)u2.x;
    output[7] = (float)u2.y;

    output[8] = (float)u4.x;
    output[9] = (float)u4.y;
    output[10] = (float)u4.z;
    output[11] = (float)u4.w;

    output[12] = f2.x;
    output[13] = f2.y;

    output[14] = f4.x;
    output[15] = f4.y;
    output[16] = f4.z;
    output[17] = f4.w;
}
