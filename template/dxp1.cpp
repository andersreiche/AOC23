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

uint64_t run() {
  uint64_t result = 0;
  std::ifstream file("puzzleInput.txt");
  std::string line;
  std::string instructions;

  while (std::getline(file, line)) {

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