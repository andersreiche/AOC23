#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std::chrono;


int calculatePointsFromMatches(int x) {
    return pow(2, x - 1);
}

int countMatches(const std::string& inputString) {
    std::vector<int> leftNumbers, rightNumbers;

    // Use stringstream to parse the numbers from the input string
    std::istringstream iss(inputString);

    // Skip the initial part of the string (before the colon)
    std::string temp;
    iss >> temp >> temp;

    // Read numbers into left vector until '|' is encountered
    int num;
    while (iss >> num) {
        leftNumbers.push_back(num);
    }

    // Clear the fail state to allow further extraction
    iss.clear();
    iss >> temp; // throw away the '|'
    // Read numbers into right vector after '|'
    while (iss >> num) {
        rightNumbers.push_back(num);
    }

    // Return the number of matches (common elements) between the two vectors
    int matchCount = 0;
    for (int num : leftNumbers) {
        if (std::find(rightNumbers.begin(), rightNumbers.end(), num) != rightNumbers.end()) {
            matchCount++;
        }
    }

    return matchCount;
}

int scratchCard(std::string card) {
  return calculatePointsFromMatches(countMatches(card));
}

uint64_t run() {
  uint64_t result = 0;
  std::ifstream file("puzzleInput.txt");
  std::string line;
  while (std::getline(file, line)) {
    result += scratchCard(line);
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