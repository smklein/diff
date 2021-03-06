#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "lib/diff.h"

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

  std::cout << ">> Diff from: " << std::endl;
  std::cout << Colorize(Color::Yellow, a) << std::endl;
  std::cout << ">> to: " << std::endl;
  std::cout << Colorize(Color::Yellow, b) << std::endl;

  for (auto [action, text] : path) {
    switch (action) {
    case DiffAction::Add:
      std::cout << Colorize(Color::Green, text);
      break;
    case DiffAction::Remove:
      std::cout << Colorize(Color::Red, text);
      break;
    case DiffAction::Same:
      std::cout << Colorize(Color::White, text);
      break;
    }
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  PrintDiff("ABCABBA", "CBABAC");
  PrintDiff(
"This text has\n" \
"multiple lines,\n" \
"isn't that neat?",
"This text has\n" \
"so many lines,\n" \
"isn't that neat?");
  return 0;
}
