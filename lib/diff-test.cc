#include "diff.h"
#include "gtest/gtest.h"

TEST(DiffTest, OnePlusOne) {
  EXPECT_EQ(2, 1 + 1);
}

TEST(DiffTest, NullComparison) {
  EXPECT_EQ({}, Diff("", ""));
}

TEST(DiffTest, IdenticalStrings) {
  EXPECT_EQ({ Same("ABC") }, Diff("ABC", "ABC"));
}

TEST(DiffTest, DistinctStrings) {
  EXPECT_EQ({ Remove("ABC"), Add("DEF") }, Diff("ABC", "DEF"));
}

TEST(DiffTest, PrefixInsertion) {
  EXPECT_EQ({ Add("ABC"), Same("DEF") }, Diff("DEF", "ABCDEF"));
}

TEST(DiffTest, SuffixInsertion) {
  EXPECT_EQ({ Same("ABC"), Add("DEF") }, Diff("ABC", "ABCDEF"));
}

TEST(DiffTest, PrefixDeletion) {
  EXPECT_EQ({ Remove("ABC"), Same("DEF") }, Diff("ABCDEF", "DEF"));
}

TEST(DiffTest, SuffixDeletion) {
  EXPECT_EQ({ Same("ABC"), Remove("DEF") }, Diff("ABCDEF", "ABC"));
}
