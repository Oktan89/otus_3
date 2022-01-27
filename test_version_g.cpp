#include "lib.h"
#include <gtest/gtest.h>


TEST(testVersionGoogle, testValidVersion) {

  EXPECT_GT(version(), 0);
}
