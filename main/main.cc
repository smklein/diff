#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "diff.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

enum class Color {
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,
};

std::string Colorize(Color c, std::string input) {
  switch (c) {
  case Color::Black: return BLACK + input + RESET;
  case Color::Red: return RED + input + RESET;
  case Color::Green: return GREEN + input + RESET;
  case Color::Yellow: return YELLOW + input + RESET;
  case Color::Blue: return BLUE + input + RESET;
  case Color::Magenta: return MAGENTA + input + RESET;
  case Color::Cyan: return CYAN + input + RESET;
  case Color::White: return WHITE + input + RESET;
  default: return input;
  }
}

void PrintDiff(const std::string& a, const std::string& b) {
  auto path = Diff(a, b);

  std::cout << "Diff from " << a << " to " << b << ":" << std::endl;

  // Coordinates:
  for (auto [x, y] : path) {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
  }

  // Prettier diff:
  int x_prev = 0;
  int y_prev = 0;
  for (auto [x, y] : path) {
    while (x_prev < x && y_prev < y) {
      std::cout << "  (Both) X: " << x_prev << " --> " << x << std::endl;
      std::cout << "  (Both) Y: " << y_prev << " --> " << y << std::endl;
//      assert(a[x_prev] == b[y_prev]);
      std::string output;
      output += a[x_prev];
      std::cout << output << std::endl;
      x_prev++;
      y_prev++;
    }
    while (x_prev < x) {
      std::cout << "  X: " << x_prev << " --> " << x << std::endl;
      std::string output;
      output += "-";
      output += a[x_prev++];
      std::cout << output << std::endl;
    }
    while (y_prev < y) {
      std::cout << "  Y: " << y_prev << " --> " << y << std::endl;
      std::string output;
      output += "+";
      output += b[y_prev++];
      std::cout << output << std::endl;
    }
  }
}

int main(int argc, char** argv) {
  PrintDiff("ABCABBA", "CBABAC");
  return 0;
}