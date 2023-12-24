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


using namespace std::chrono;

int getCardValue(char c) {
  std::string valueOrder = "23456789TJQKA";
  for (int i = 0; i < valueOrder.length(); ++i) {
    if (valueOrder[i] == c) {
      return i;
    }
  }
  return -1;
}

int getHandType(const std::string& str) {
  std::map<char, int> countMap;

  // Initialize the map with keys.
  std::string valueOrder = "23456789TJQKA";
  for (char key : valueOrder) {
    countMap[key] = 0;
  }

  // Count occurrences of each letter in the input string.
  for (char c : str) {
    if (countMap.find(c) != countMap.end()) {
      countMap[c]++;
    }
  }

  // count dublicates
  int maxCount = 0;
  for (const auto& pair : countMap) {
    if (pair.second > maxCount) {
      maxCount = pair.second;
    }
  }

  // full house check
  if (maxCount == 3) {
    for (const auto& pair : countMap) {
      if (pair.second == 2) {
        return 5; // full house
      }
    }
  }

  // 2 pairs check
  int pairCount = 0;
  if (maxCount == 2) {
    for (const auto& pair : countMap) {
      if (pair.second == 2) {
        pairCount++;
        if (pairCount == 2) {
          return 3; // 2 pairs
        }
      }
    }
  }

  switch (maxCount) {
    case 1: // high card
      return 1; 
    case 2: // pair
      return 2; 
    case 3: // three of a kind
      return 4; 
    case 4: // four of a kind
      return 6; 
    case 5: // five of a kind
      return 7; 
  }
  return -1;
}

bool leftHandIsHigher(const std::string& lhs, const std::string& rhs) {
  if (getHandType(lhs) > getHandType(rhs)) {
    return true;
  }
  if (getHandType(lhs) < getHandType(rhs)) {
    return false;
  }
  for (int i = 0; i < lhs.length(); ++i) {
    if (getCardValue(lhs[i]) > getCardValue(rhs[i])) {
      return true;
    }
    if (getCardValue(lhs[i]) < getCardValue(rhs[i])) {
      return false;
    }
  }
}

struct Hand {
  std::string hand;
  int bid;
  Hand(int b, const std::string& h) : bid(b), hand(h) {}
};

std::vector<Hand> hands;

uint64_t run() {
  uint64_t result = 0;
  std::ifstream file("testInput.txt");
  std::string line;
  std::string hand;
  int bid = 0;

  // 1. read all hands into a vector.
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    iss >> hand;
    iss >> bid;
    hands.push_back(Hand(bid, hand));
  }

  
  // 2. quicksort hands using prioritized criteria: hand type -> card 1 --> card 2 ...
  // Compare function -> leftHandIsHigher(lhs, rhs);
  
  // 3. loop the hands using index = rank and multiply each bid with index.
  // 4. sum up all scores.

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