#include <ctime>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "diff.h"

void PrintDiff(const std::string& a, const std::string& b) {
  auto path = Diff(a, b);

  for (auto [x, y] : path) {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
  }
}

int main(int argc, char** argv) {
  PrintDiff("ABCABBA", "CBABAC");
  return 0;
}
