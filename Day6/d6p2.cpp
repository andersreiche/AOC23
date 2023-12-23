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


using namespace std::chrono;

std::vector<int> times;
std::vector<int> distances;

uint64_t getDistance(uint64_t timeRemaining, uint64_t speed) {
    return speed * timeRemaining;
}

uint64_t combineIntegers(const std::vector<int>& integers) {
    std::string result;

    for (int num : integers) {
        result += std::to_string(num);
    }

    return std::stoull(result);
}

uint64_t run() {
  uint64_t result = 0;
  std::ifstream file("puzzleInput.txt");
  std::string line;
  std::string tmp;
  std::getline(file, line);
  std::istringstream iss(line);
  iss >> tmp; // throw away label
  uint64_t num = 0;
  while (iss >> num) {
      times.push_back(num);
  }
  std::getline(file, line);
  std::istringstream iss2(line);
  iss2 >> tmp; // throw away label
  while (iss2 >> num) {
      distances.push_back(num);
  }

  uint64_t distance = combineIntegers(distances);
  uint64_t time = combineIntegers(times);

  for (uint64_t delay = 1; delay < time; delay++) { // skip 0 speed and full wait
    uint64_t timeRemaining = time - delay;
    uint64_t currentDistance = getDistance(timeRemaining, delay);
    if (currentDistance > distance) {
      result++;
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