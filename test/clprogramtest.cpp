#include "clprogramtest.h"

#include <clprogram.h>

#include "errorassert.h"

ClProgramTest::ClProgramTest() : NeedsClContext(), error() { }

ClProgramTest::~ClProgramTest() { }

// Test creating, building and querying correct OpenCL programs.
TEST_F(ClProgramTest, good) {
    // create & build program
    ClProgram program(error, *c, "good.cl"); ASSERT_OK(error);
    cl_build_status status = program.buildStatus(error, *d); ASSERT_OK(error);
    EXPECT_EQ(CL_BUILD_NONE, status);
    program.build(error, *d, ""); ASSERT_OK(error);

    // query program object
    status = program.buildStatus(error, *d); ASSERT_OK(error);
    ASSERT_EQ(CL_BUILD_SUCCESS, status) << "Build of good.cl failed.";
    program.buildStatusString(error, *d); ASSERT_OK(error);
    program.buildOptions(error, *d); ASSERT_OK(error);
    program.buildLog(error, *d); ASSERT_OK(error);
    QByteArray binary = program.getBinary(error, *d); ASSERT_OK(error);

    // create program from binary
    ClProgram program2(error, *c, *d, binary); ASSERT_OK(error);
    status = program2.buildStatus(error, *d); ASSERT_OK(error);
    EXPECT_EQ(CL_BUILD_NONE, status);
}

// Test creating and trying to build a program from invalid source code.
TEST_F(ClProgramTest, bad) {
    // create program from source
    ClProgram program(error, *c, "bad.cl"); ASSERT_OK(error);
    cl_build_status status = program.buildStatus(error, *d); ASSERT_OK(error);
    EXPECT_EQ(CL_BUILD_NONE, status);

    // try to build program
    program.build(error, *d, "");
    EXPECT_ERR(error) << "Building bad.cl should raise error.";

    // query program object
    status = program.buildStatus(error, *d); ASSERT_OK(error);
    ASSERT_EQ(CL_BUILD_ERROR, status);
    program.buildStatusString(error, *d); ASSERT_OK(error);
    program.buildOptions(error, *d); ASSERT_OK(error);
    program.buildLog(error, *d); ASSERT_OK(error);
}

// Test trying to load a program from a nonexistent file.
TEST_F(ClProgramTest, wrongFilename) {
    ClProgram program(error, *c, "noSuchFile.cl");
    EXPECT_ERR(error) << "Trying to load nonexistent file should raise error.";
}

// Test building a program that seems to cause problems in OS X 10.8.
TEST_F(ClProgramTest, mountainLionIssue) {
    ClProgram program(error, *c, "mountainLionIssue.cl"); ASSERT_OK(error);
    cl_build_status status = program.buildStatus(error, *d); ASSERT_OK(error);
    EXPECT_EQ(CL_BUILD_NONE, status);
    program.build(error, *d, ""); ASSERT_OK(error);
    status = program.buildStatus(error, *d); ASSERT_OK(error);
    EXPECT_EQ(CL_BUILD_SUCCESS, status)
    << "Build of mountainLionIssue.cl failed.";
}
