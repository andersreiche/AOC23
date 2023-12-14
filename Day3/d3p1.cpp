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
  std::cout << c << std::endl;
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
  

  for (int i = startIndex -1; i < stopIndex + 1; i++) {
      if (isSymbol(topLine[i])) return true;
      if (isSymbol(bottomLine[i])) return true;
  }

  return false;
}

int run() {
  std::ifstream file("puzzleInput.txt");
  std::string topLine;
  std::string middleLine;
  std::string bottomLine;
  int sum = 0;
  std::getline(file, topLine);
  std::getline(file, middleLine);
  size_t startIndex = 0;
  size_t stopIndex = 0;
  while (std::getline(file, bottomLine)) {
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
  return sum;
}

int main() {
  auto start = high_resolution_clock::now();
  int result = run();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "result: " << result << std::endl;
  std::cout << "Code executed in: " << duration.count() << " microseconds." << std::endl;
}