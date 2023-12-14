#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std::chrono;


bool isSymbol(char c) {
  if (c == '.') return false;
  if (!std::isalnum(c)) {
    return true;
  }
  return false;
}

bool isPartNo(size_t startIndex, size_t stopIndex, std::string topLine, std::string middleLine, std::string bottomLine) {
  if (startIndex > 0) {
    if (isSymbol(middleLine[startIndex -1])) return true;
  } else {
    startIndex++;
  }
  if (stopIndex < middleLine.length() - 1) {
    if (isSymbol(middleLine[stopIndex +1])) return true;
  } else {
    stopIndex--;
  }

  for (int i = startIndex -1; i <= stopIndex + 1; i++) {
      if (isSymbol(topLine[i])) return true;
      if (isSymbol(bottomLine[i])) return true;
  }

  return false;
}

uint64_t run() {
  // std::ifstream file("puzzleInput.txt");
  std::ifstream file("puzzleInput.txt");
  std::string topLine;
  std::string middleLine;
  std::string bottomLine;
  uint64_t sum = 0;
  std::getline(file, middleLine);
  topLine.assign(middleLine.length(), '.');
  size_t startIndex = 0;
  size_t stopIndex = 0;
  bool loop = true;
  while (loop) {
    if (!std::getline(file, bottomLine)) {
      bottomLine.assign(middleLine.length(), '.');
      loop = false;
    }
    while (true) {
      startIndex = middleLine.find_first_of("1234567890", startIndex);
      if (startIndex == 0) {
        startIndex = 0;
      }
      if (startIndex == std::string::npos){
        startIndex = 0;
        break;
      } 
      stopIndex = middleLine.find_first_not_of("1234567890", startIndex) - 1;
      if (stopIndex + 1 == std::string::npos){
        stopIndex = middleLine.length() - 1;
      } 
      if(isPartNo(startIndex, stopIndex, topLine, middleLine, bottomLine)) {
        std::string numberString = middleLine.substr(startIndex, stopIndex + 1 - startIndex);
        sum += std::stoi(numberString);
      }
      startIndex = stopIndex + 1;

    }
    topLine = middleLine;
    middleLine = bottomLine;
  }
  // missing last line
  return sum;
}

int main() {
  auto start = high_resolution_clock::now();
  uint64_t result = run();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "result: " << result << std::endl;
  std::cout << "Code executed in: " << duration.count() << " microseconds." << std::endl;
}