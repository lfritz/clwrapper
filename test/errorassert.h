#pragma once

// Googletest assertion macros for Error class.

#include <gtest/gtest.h>

class Error;

testing::AssertionResult assertOK(const char *, Error& error);

testing::AssertionResult assertErr(const char *, Error& error);

#define ASSERT_OK(error) ASSERT_PRED_FORMAT1(assertOK, error)

#define EXPECT_OK(error) EXPECT_PRED_FORMAT1(assertOK, error)

#define ASSERT_ERR(error) ASSERT_PRED_FORMAT1(assertErr, error)

#define EXPECT_ERR(error) EXPECT_PRED_FORMAT1(assertErr, error)
