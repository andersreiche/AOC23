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

std::vector<int64_t> makeDiffArray(std::vector<int64_t> history) {
  std::vector<int64_t> diffArray;
  for (size_t i = 1; i < history.size(); i++) { 
    diffArray.push_back((history[i] - history[i-1]));
  }
  return diffArray;
}

bool vectorIsZero(std::vector<int64_t> vector) {
  return std::all_of(vector.begin(), vector.end(), [](int64_t value) {
      return value == 0;
  });
}

std::vector<std::vector<int64_t>> makeDiffStack(std::vector<int64_t> history) {
  std::vector<std::vector<int64_t>> diffStack;
  std::vector<int64_t> diffArray = history;
  while (true) {
    diffArray = makeDiffArray(diffArray);
    diffStack.push_back(diffArray);
    if (vectorIsZero(diffArray)) { break; }
  }
  std::reverse(diffStack.begin(), diffStack.end());
  return diffStack;
}

int64_t getNextHistoryValue (std::vector<int64_t> history) {
  int64_t nextHistoryValue = 0;
  std::vector<std::vector<int64_t>> diffStack = makeDiffStack(history);
  for (size_t i = 1; i < diffStack.size(); i++) { 
    diffStack[i].push_back((diffStack[i].back() + diffStack[i-1].back()));
  }
  return diffStack.back().back() + history.back();
}

int64_t run() {
  std::vector<std::vector<int64_t>> histories;
  int64_t result = 0;
  std::ifstream file("puzzleInput.txt");
  std::string line;

  while (std::getline(file, line)) {
    std::vector<int64_t> history;
    std::istringstream iss(line);
    int64_t num;
    while (iss >> num) {
      history.push_back(num);
    }
    histories.push_back(history);
  }

  for (auto& history : histories) {
    int64_t nextHistoryValue = getNextHistoryValue(history);
    result += nextHistoryValue;
  }

  return result;
}

int main() {
  auto start = high_resolution_clock::now();
  int64_t result = run();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "result: " << result << std::endl;
  std::cout << "Code executed in: " << duration.count() << " microseconds." << std::endl;
}