#include <assert.h>

#include <algorithm>
#include <optional>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "diff.h"

struct CoordinateHash {
  std::size_t operator()(Coordinate const& c) const noexcept {
    auto [x, y] = c;
    return std::hash<int>{}(x) ^ (std::hash<int>{}(y << 1));
  }
};

// TODO: Decouple coordinate system, helpers, from walking class.
// TODO: Decouple from string.
// TODO: Customize walking order preferences.
class PathWalker {
public:
  PathWalker(const std::string& lhs, const std::string& rhs) : lhs_(lhs), rhs_(rhs) {
    Coordinate origin(0, 0);
    paths_[origin] = std::nullopt;
    working_set_.push(origin);
    auto d_origin = TakeFreeDiagonals(origin);
    if (d_origin != origin) {
      InsertNewPath(origin, d_origin);
    }
  }

  // The output is a sequence of coordinates (X, Y), where:
  //   "+X" implies deletion of a character from the input string A.
  //   "+Y" implies insertion of a character from the input string B.
  //   "+X, +Y" implies no diff between the two strings.
  std::vector<Coordinate> Walk() {
    while (!working_set_.empty()) {
      auto coordinate = working_set_.front();
      working_set_.pop();
      auto [x, y] = coordinate;

      if (x < CapacityX()) {
        auto cx = Coordinate(x + 1, y);
        InsertNewPath(coordinate, cx);
        auto dcx = TakeFreeDiagonals(cx);
        if (cx != dcx) {
          InsertNewPath(cx, dcx);
        }
        if (dcx == Terminus()) {
          break;
        }
      }

      if (y < CapacityY()) {
        auto cy = Coordinate(x, y + 1);
        InsertNewPath(coordinate, cy);
        auto dcy = TakeFreeDiagonals(cy);
        if (cy != dcy) {
          InsertNewPath(cy, dcy);
        }
        if (dcy == Terminus()) {
          break;
        }
      }
    }
    return Enumerate();
  }

private:
  // Enumerates the full path from the Terminus to the origin.
  //
  // Precondition: Terminus in |paths_|.
  std::vector<Coordinate> Enumerate() const {
    std::vector<Coordinate> result;
    auto coordinate = Terminus();
    while (true) {
      result.push_back(coordinate);
      auto maybe_coordinate = paths_.at(coordinate);
      if (maybe_coordinate == std::nullopt) {
        break;
      }
      coordinate = *maybe_coordinate;
    }
    std::reverse(result.begin(), result.end());
    return result;
  }

  Coordinate TakeFreeDiagonals(Coordinate source) const {
    Coordinate result = source;
    auto [x, y] = result;
    while (x < CapacityX() && y < CapacityY() && lhs_[x] == rhs_[y]) {
      result = Coordinate(++x, ++y);
    }
    return result;
  }

  // Inserts a new path from |parent| to |child|.
  // No-op if a path to |child| already exists.
  void InsertNewPath(Coordinate parent, Coordinate child) {
    if (paths_.find(child) != paths_.end()) {
      return;
    }

    auto grandparent = paths_[parent];
    if (grandparent != std::nullopt &&
        TransformationType(*grandparent, parent) == TransformationType(parent, child)) {
      // Coalesce multiple operations of the same type (multi-add, multi-delete).
      paths_[child] = *grandparent;
    } else {
      paths_[child] = parent;
    }
    working_set_.push(child);
  }

  // Compares a parent and child coordinate, returning the type of the traversal.
  //
  // Precondition: A path must exist from |parent| to |child|, such that a single
  // repeated move (addition, subtraction, or no diff) can transform the parent
  // coordinate to the child coordinate.
  static DiffAction TransformationType(Coordinate parent, Coordinate child) {
    auto [x1, y1] = parent;
    auto [x2, y2] = child;
    if (x1 != x2 && y1 != y2) {
      assert(x2 - x1 == y2 - y1);
      return DiffAction::Same;
    } else if (x1 != x2) {
      assert(y1 == y2);
      return DiffAction::Remove;
    } else {
      assert(x1 == x2);
      return DiffAction::Add;
    }
  }

  const int CapacityX() const { return lhs_.length(); }
  const int CapacityY() const { return rhs_.length(); }

  const Coordinate Terminus() const {
    return Coordinate(CapacityX(), CapacityY());
  }

  // A mapping of "coordinate" --> "parent coordinate" used to reach this spot.
  // Optional for the case of the root coordinate (0, 0), which has no parent.
  std::unordered_map<Coordinate, std::optional<Coordinate>, CoordinateHash> paths_;
  std::queue<Coordinate> working_set_;
  const std::string& lhs_;
  const std::string& rhs_;
};

std::vector<DiffResult> Diff(const std::string& lhs, const std::string& rhs) {
  PathWalker path_walker(lhs, rhs);
  auto coords = path_walker.Walk();

  std::vector<DiffResult> result;
  int x_prev = 0;
  int y_prev = 0;
  for (auto [x, y] : coords) {
    std::string output;
    // Case 1: No diff.
    while (x_prev < x && y_prev < y) {
      output += lhs[x_prev];
      x_prev++;
      y_prev++;
    }
    if (output != "") {
      result.push_back({ DiffAction::Same, output });
      output = "";
    }

    // Case 2: Deletion.
    while (x_prev < x) {
      output += lhs[x_prev++];
    }
    if (output != "") {
      result.push_back({ DiffAction::Remove, output });
      output = "";
    }

    // Case 3: Insertion.
    while (y_prev < y) {
      output += rhs[y_prev++];
    }
    if (output != "") {
      result.push_back({ DiffAction::Add, output });
      output = "";
    }
  }

  return result;
}

bool operator==(const DiffResult& lhs, const DiffResult& rhs) {
  return lhs.action == rhs.action && lhs.string == rhs.string;
}
