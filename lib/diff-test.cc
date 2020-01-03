#include "diff.h"
#include "gtest/gtest.h"

TEST(DiffTest, NullComparison) {
  auto result = Diff("", "");
  EXPECT_TRUE(result.empty());
}

TEST(DiffTest, IdenticalStrings) {
  std::vector<DiffResult> result = {
    {
      DiffAction::Same,
      "ABC",
    },
  };

  EXPECT_EQ(result, Diff("ABC", "ABC"));
}

TEST(DiffTest, DistinctStrings) {
  std::vector<DiffResult> result = {
    {
      DiffAction::Remove,
      "ABC",
    },
    {
      DiffAction::Add,
      "DEF",
    },
  };
  EXPECT_EQ(result, Diff("ABC", "DEF"));
}

TEST(DiffTest, PrefixInsertion) {
  std::vector<DiffResult> result = {
    {
      DiffAction::Add,
      "ABC",
    },
    {
      DiffAction::Same,
      "DEF",
    },
  };
  EXPECT_EQ(result, Diff("DEF", "ABCDEF"));
}

TEST(DiffTest, SuffixInsertion) {
  std::vector<DiffResult> result = {
    {
      DiffAction::Same,
      "ABC",
    },
    {
      DiffAction::Add,
      "DEF",
    },
  };
  EXPECT_EQ(result, Diff("ABC", "ABCDEF"));
}

TEST(DiffTest, PrefixDeletion) {
  std::vector<DiffResult> result = {
    {
      DiffAction::Remove,
      "ABC",
    },
    {
      DiffAction::Same,
      "DEF",
    },
  };
  EXPECT_EQ(result, Diff("ABCDEF", "DEF"));
}

TEST(DiffTest, SuffixDeletion) {
  std::vector<DiffResult> result = {
    {
      DiffAction::Same,
      "ABC",
    },
    {
      DiffAction::Remove,
      "DEF",
    },
  };
  EXPECT_EQ(result, Diff("ABCDEF", "ABC"));
}
