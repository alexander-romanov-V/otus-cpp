#include "lib.h"

#include <gtest/gtest.h>
// #include <gmock/gmock.h>

TEST(TestGroupName, Subtest_1) {
  EXPECT_GT(version(), 0);
  std::cout << "continue test after failure" <<std:: endl;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
//   ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}
