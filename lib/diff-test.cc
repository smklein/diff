#include "diff.h"
#include "gtest/gtest.h"

TEST(DiffTest, OnePlusOne) {
  EXPECT_EQ(2, 1 + 1);
}

TEST(DiffTest, NullDiff) {
  auto result = Diff("", "");
  for (auto e : result) {
    std::cout << std::get<0>(e) << ", " << std::get<1>(e) << std::endl;
  }
  EXPECT_TRUE(result.empty());
}
