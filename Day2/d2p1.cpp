#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std::chrono;

const int maxRed = 12;
const int maxGreen = 13;
const int maxBlue = 14;

int run() {
  std::ifstream file("puzzleInput.txt");
  std::string line;
  int sum = 0;

  while (std::getline(file, line)) { // GAMES in the file
      bool validGame = true;
      size_t idStartPos = line.find(' ');
      size_t idEndPos = line.find(':');
      std::string gameIdStr = line.substr(idStartPos, idEndPos - idStartPos);
      int gameId = std::stoi(gameIdStr);
      size_t startSetPos = idEndPos + 2;
      size_t endSetPos = line.find(';', startSetPos);
      std::string set = line.substr(startSetPos, endSetPos - startSetPos);
      size_t startPairPos = 0;
      while (true) { // SETS in the game
          size_t endPairPos = set.find_first_of(';,');
          while (true) { // PAIRS in the set
                size_t numberStartPos = startPairPos;
                size_t numberEndPos = set.find(' ', numberStartPos);
                int amount = std::stoi(set.substr(numberStartPos, numberEndPos - numberStartPos));
                size_t colorStartPos =  numberEndPos + 1;
                size_t colorEndPos = set.find_first_not_of("bluegrdn", colorStartPos); // letters in blue, green, red.
                std::string color = set.substr(colorStartPos, colorEndPos - colorStartPos);
                std::string pair = set.substr(numberStartPos, colorEndPos - numberStartPos);
                if ((color == "red" && amount > maxRed) || (color == "green" && amount > maxGreen) || (color == "blue" && amount > maxBlue)) {
                    validGame = false;
                    break;
                }
                if (endPairPos == std::string::npos) {
                  startPairPos = 0;
                  break; // This was the last pair in the set
                }
                startPairPos = endPairPos + 2; // skip the , or ; and the space
                endPairPos = set.find_first_of(';,', startPairPos);
          }
          if (!validGame) break;
          startSetPos = endSetPos + 2; // skip semicolon and space
          if (startSetPos >= line.length()) break;
          endSetPos = line.find(';', startSetPos);
          endSetPos = (endSetPos == std::string::npos) ? line.length() : endSetPos;
          set = line.substr(startSetPos, endSetPos - startSetPos);
        }
        if (validGame) sum += gameId;
    }
    return sum;
}

int main() {
  auto start = high_resolution_clock::now();
  int sum = run();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "sum: " << sum << std::endl;
  std::cout << "Code executed in: " << duration.count() << " microseconds." << std::endl;
}