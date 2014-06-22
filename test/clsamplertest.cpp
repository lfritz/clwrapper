#include "clsamplertest.h"

#include <clsampler.h>

#include "errorassert.h"

ClSamplerTest::ClSamplerTest() : NeedsClContext(), error() { }

ClSamplerTest::~ClSamplerTest() { }

// Create sampler and check its properties.
TEST_F(ClSamplerTest, create) {
    bool normalizedCoords = false;
    cl_addressing_mode addressingMode = CL_ADDRESS_CLAMP;
    cl_filter_mode filterMode = CL_FILTER_NEAREST;
    ClSampler sampler(error, *c, normalizedCoords, addressingMode, filterMode);
    ASSERT_OK(error);

    bool n = sampler.getNormalizedCoords(error); ASSERT_OK(error);
    cl_addressing_mode am = sampler.getAddressingMode(error); ASSERT_OK(error);
    cl_filter_mode fm = sampler.getFilterMode(error); ASSERT_OK(error);
    EXPECT_EQ(normalizedCoords, n) <<
    "sampler parameter normalized_coords is not as specified";
    EXPECT_EQ(addressingMode, am) <<
    "sampler parameter addressing mode is not as specified";
    EXPECT_EQ(filterMode, fm) <<
    "sampler parameter filter mode is not as specified";
}
