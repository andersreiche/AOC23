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
#include <numeric>

using namespace std::chrono;
 
// Greatest common denominator
int64_t gcd(int64_t a, int64_t b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// least common multiple
int64_t lcm(std::vector<int64_t> numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), static_cast<int64_t>(1),
        [](int64_t x, int64_t y) { return (x * y) / gcd(static_cast<int64_t>(x), y); });
}

struct Node {
  std::string L;
  std::string R;
  Node() {}
  Node(const std::string& l, const std::string& r) : L(l), R(r) {}
};

std::map<std::string, Node> nodeMap;

int64_t run() {
  std::ifstream file("puzzleInput.txt");
  std::string line;
  std::string instructions;
  std::getline(file, instructions);
  std::getline(file, line); // throw away empty line

  std::regex pattern(R"(\s*([\w\d]+)\s*=\s*\(([\w\d]+),\s*([\w\d]+)\)\s*)");

  std::smatch matches;

  // populate map
  while (std::getline(file, line)) {
    std::regex_match(line, matches, pattern); // matches = name, left, right
    nodeMap[matches[1]] = Node(matches[2], matches[3]);
  }

  // Find starting locations
  std::list<std::string> locations;
  for (const auto& pair : nodeMap) {
      const std::string& key = pair.first;
      if (key.back() == 'A') {
        locations.push_back(key);
      }
  }

  // walk map to get loop lengths
  std::vector<int64_t> loopLengths;
  for (auto& location : locations) { 
    int64_t steps = 0;
    while(location.back() != 'Z') {
      for (auto instruction : instructions) {
        if (instruction == 'R') {
          location = nodeMap[location].R;
        } else if (instruction == 'L') {
          location = nodeMap[location].L;
        }
        steps++;
        if (location.back() == 'Z') { break; }
      }
    }
    loopLengths.push_back(steps);
  }
  return lcm(loopLengths);
}

int main() {
  auto start = high_resolution_clock::now();
  int64_t result = run();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "result: " << result << std::endl;
  std::cout << "Code executed in: " << duration.count() << " microseconds." << std::endl;
}