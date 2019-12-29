#include <string>
#include <tuple>
#include <vector>

using Coordinate = std::tuple<int, int>;

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
std::vector<Coordinate> Diff(const std::string& a, const std::string& b);