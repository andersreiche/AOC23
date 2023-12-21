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

std::unordered_map<int, std::string> originalCards;

struct Card {
    int cardNumber;
    std::string content;

    // Constructor to initialize the card with values
    Card(int number, const std::string& text) : cardNumber(number), content(text) {}
};


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
  return countMatches(card);
}

uint64_t run() {
  std::list<Card> cards;
  uint64_t result = 0;
  std::ifstream file("puzzleInput.txt");
  std::string line;
  int lineNo = 0;
  while (std::getline(file, line)) {
    lineNo++;
    // Put each card into an unsorted map with the line index as the key, and line as value
    originalCards[lineNo] = line;
    // Add them to the card list to make it easier to parse all cards in 1 go.
    cards.push_back(Card(lineNo, line));

  }
  // Scratch each original card. For winners, add the copies to a dynamic list of copies. up to score
  // loop the dynamic list while adding winners to the end of the list. 
  for (const auto& card : cards) {
    int result = scratchCard(card.content);
    for (int i = 1; i <= result; i++) {
      int cardKey = card.cardNumber + i;
      std::string originalCard = originalCards[cardKey];
      cards.push_back(Card(cardKey, originalCard));
    }
  }
  return cards.size();
}

int main() {
  auto start = high_resolution_clock::now();
  uint64_t result = run();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "result: " << result << std::endl;
  std::cout << "Code executed in: " << duration.count() << " microseconds." << std::endl;
}