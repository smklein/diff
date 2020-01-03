#include <string>
#include <tuple>
#include <vector>

using Coordinate = std::tuple<int, int>;

enum class DiffAction {
  Add,
  Remove,
  Same,
};

struct DiffResult {
  DiffAction action;
  std::string string;
};

bool operator==(const DiffResult& lhs, const DiffResult& rhs) {
  return lhs.action == rhs.action && lhs.string == rhs.string;
}

// Returns a sequence of coordinates describing the diff between two strings.
//
// The output is a sequence of coordinates (X, Y), where:
//   "+X" implies deletion of a character from the input string A.
//   "+Y" implies insertion of a character from the input string B.
//   "+X, +Y" implies no diff between the two strings.
//
// TODO(smklein): Tests!
// TODO(smklein): Generalize to non-strings.
// TODO(smklein): More strongly-typed output.
std::vector<DiffResult> Diff(const std::string& a, const std::string& b);
