#pragma once

inline void toSizeTArray(size_t array[3], glm::ivec3 vec) {
    array[0] = vec.x;
    array[1] = vec.y;
    array[2] = vec.z;
}
