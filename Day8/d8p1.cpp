#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>
#include <unordered_map>
#include <map>
#include <regex>

using namespace std::chrono;

struct Node {
  std::string L;
  std::string R;
  Node() {}
  Node(const std::string& l, const std::string& r) : L(l), R(r) {}
};

std::map<std::string, Node> nodeMap;

uint64_t run() {
  uint64_t result = 0;
  std::ifstream file("puzzleInput.txt");
  std::string line;
  std::string instructions;
  std::getline(file, instructions);
  std::getline(file, line); // throw away empty line

  std::regex pattern(R"(\s*([A-Z]+)\s*=\s*\((\w+),\s*(\w+)\)\s*)");
  std::smatch matches;

  // populate map
  while (std::getline(file, line)) {
    std::regex_match(line, matches, pattern); // matches = name, left, right
    nodeMap[matches[1]] = Node(matches[2], matches[3]);
  }

  // walk map
  std::string location = "AAA";
  while(location != "ZZZ") {
    for (auto instruction : instructions) {
      if (instruction == 'R') {
        location = nodeMap[location].R;
      } else if (instruction == 'L') {
        location = nodeMap[location].L;
      }
      result++;
      if (location == "ZZZ") {
        break;
      }
    }
  }

  return result;
}

int main() {
  auto start = high_resolution_clock::now();
  uint64_t result = run();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "result: " << result << std::endl;
  std::cout << "Code executed in: " << duration.count() << " microseconds." << std::endl;
}