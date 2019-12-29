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
    InsertNewPath(origin, d_origin, d_origin);
  }

  std::vector<Coordinate> Walk() {
    while (!working_set_.empty()) {
      auto coordinate = working_set_.front();
      working_set_.pop();
      auto [x, y] = coordinate;

      if (x < CapacityX()) {
        auto cx = Coordinate(x + 1, y);
        auto dcx = TakeFreeDiagonals(cx);
        InsertNewPath(coordinate, cx, dcx);
        if (dcx == Terminus()) {
          break;
        }
      }

      if (y < CapacityY()) {
        auto cy = Coordinate(x, y + 1);
        auto dcy = TakeFreeDiagonals(cy);
        InsertNewPath(coordinate, cy, dcy);
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
  void InsertNewPath(Coordinate parent, Coordinate child, Coordinate diagonal) {
    if (paths_.find(child) != paths_.end() ||
        paths_.find(diagonal) != paths_.end()) {
      return;
    }

    if (child != diagonal) {
      paths_[child] = parent;
      parent = child;
    }
    paths_[diagonal] = parent;
    working_set_.push(diagonal);
  }

  const int CapacityX() const { return lhs_.length(); }
  const int CapacityY() const { return rhs_.length(); }

  const Coordinate Terminus() const {
    return Coordinate(CapacityX(), CapacityY());
  }

  std::unordered_map<Coordinate, std::optional<Coordinate>, CoordinateHash> paths_;
  std::queue<Coordinate> working_set_;
  const std::string& lhs_;
  const std::string& rhs_;
};

std::vector<Coordinate> Diff(const std::string& lhs, const std::string& rhs) {
  PathWalker path_walker(lhs, rhs);
  return path_walker.Walk();
}

// TODO: Add gtest
// TODO: create some tests
