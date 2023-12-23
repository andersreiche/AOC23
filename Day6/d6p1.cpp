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
std::vector<int> raceBeatCombinations;

int getDistance(int timeRemaining, int speed) {
    return speed * timeRemaining;
}

uint64_t run() {
  uint64_t result = 1;
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
      raceBeatCombinations.push_back(0);
  }
  for (size_t i = 0; i < times.size(); i++) {
    for (int delay = 1; delay < times[i]; delay++) { // skip 0 speed and full wait
      int timeRemaining = times[i] - delay;
      int currentDistance = getDistance(timeRemaining, delay);
      if (currentDistance > distances[i]) {
        raceBeatCombinations[i]++;
      }
    }
  }
  for (int num : raceBeatCombinations) {
    result *= num;
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