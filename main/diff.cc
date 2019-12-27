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
  }

  std::vector<Coordinate> Walk() {
    while (!working_set_.empty()) {
      auto coordinate = working_set_.front();
      working_set_.pop();
      auto [x, y] = coordinate;

      if (x < CapacityX()) {
        auto cx = TakeFreeDiagonals(Coordinate(x + 1, y));
        InsertNewPath(coordinate, cx);
        if (cx == Terminus()) {
          return Enumerate();
        }
      }

      if (y < CapacityY()) {
        auto cy = TakeFreeDiagonals(Coordinate(x, y + 1));
        InsertNewPath(coordinate, cy);
        if (cy == Terminus()) {
          return Enumerate();
        }
      }
    }
    return std::vector<Coordinate>();
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
    paths_[child] = parent;
    working_set_.push(child);
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
