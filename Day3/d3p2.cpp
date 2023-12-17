#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_map>

using namespace std::chrono;

bool isStar(char c) {
  if (c == '*') return true;
  return false;
}

std::string createUniqueId(int LineNo, int i) {
    std::string lineNoStr = "l" + std::to_string(LineNo);
    std::string iStr = "i" + std::to_string(i);
    return lineNoStr + iStr;
}

std::string getCog(size_t startIndex, size_t stopIndex, std::string topLine, std::string middleLine, std::string bottomLine, int lineNo) {
  if (startIndex > 0) {
    if (isStar(middleLine[startIndex -1])) return createUniqueId(lineNo, startIndex -1);
  } else {
    startIndex++;
  }
  if (stopIndex < middleLine.length() - 1) {
    if (isStar(middleLine[stopIndex +1])) return createUniqueId(lineNo, stopIndex +1);
  } else {
    stopIndex--;
  }

  for (int i = startIndex -1; i <= stopIndex + 1; i++) {
      if (isStar(topLine[i])) return createUniqueId(lineNo - 1, i);
      if (isStar(bottomLine[i])) return createUniqueId(lineNo + 1, i);
  }

  return "";
}

uint64_t run() {
  std::unordered_map<std::string, std::list<int>> myHashTable;
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
  int lineNo = 0;
  while (loop) {
    lineNo++;
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
      std::string cogIndex = getCog(startIndex, stopIndex, topLine, middleLine, bottomLine, lineNo);
      if(cogIndex != "") {
        std::string numberString = middleLine.substr(startIndex, stopIndex + 1 - startIndex);
        int cogNumber = std::stoi(numberString);
        myHashTable[cogIndex].push_back(cogNumber);
      }
      startIndex = stopIndex + 1;
    }
    topLine = middleLine;
    middleLine = bottomLine;
  }
  for (const auto& pair : myHashTable) {
      if (pair.second.size() == 2) {
          sum += pair.second.front() * pair.second.back();
      }
  }
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