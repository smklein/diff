#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "diff.h"

struct Node {
  Coordinate c;
  std::optional<Coordinate> parent;
};

std::vector<Coordinate> Diff(const std::string& a, const std::string& b) {
  // +X: Deletion of character from A.
  // +Y: Insertion of character from B.
  std::vector<Coordinate> result;

  //       PATHS: UNORDERED_MAP<Coordinate, Node>
  // WORKING SET: VEC<Coordinate>
  //    TERMINUS: (len(a), len(b))
  //
  // Insert { (0, 0), nullopt } Node into PATHS.
  // Insert (0, 0) into WORKING SET.
  //
  // InsertAndCheck(Parent = C, New = C'):
  //    If C' not in PATHS:
  //      Insert <C', C> into PATHS.
  //      Insert C' into WORKING SET.
  //      If C' == TERMINUS:
  //        Return Reverse(Enumerate(PATHS(C')))
  //
  // Loop:
  //  For C : Coords in WORKING SET:
  //    Create new Coord C' = TakeFreeDiagonals(C(x + 1), C(y))
  //    InsertAndCheck(C, C')
  //    Create new Coord C'' = TakeFreeDiagonals(C(x), C(y + 1))
  //    InsertAndCheck(C, C'')

  return result;
}

// TODO: Add gtest
// TODO: create some tests
