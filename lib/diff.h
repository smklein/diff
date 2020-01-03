#pragma once

#include <string>
#include <tuple>
#include <vector>

using Coordinate = std::tuple<int, int>;

enum class DiffAction {
  Add,
  Remove,
  Same,
};

// Describes a sequence of transformations to convert one string object to another.
struct DiffResult {
  DiffAction action;
  std::string string;
};

// Comparison operator for DiffResult objects.
bool operator==(const DiffResult& lhs, const DiffResult& rhs);

// Returns a sequence of coordinates describing the diff between two strings.
//
// TODO(smklein): Generalize to non-strings.
std::vector<DiffResult> Diff(const std::string& a, const std::string& b);
