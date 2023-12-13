#include <iostream>
#include <fstream>
#include <string>

const int maxRed = 12;
const int maxGreen = 13;
const int maxBlue = 14;

int main() {

    std::ifstream file("puzzleInput.txt");

    std::string line;
    int sum = 0;

    // GAMES in the file
    while (std::getline(file, line)) {
        size_t idStartPos = line.find(' ');
        size_t idEndPos = line.find(':');
        std::string gameIdStr = line.substr(idStartPos, idEndPos - idStartPos);
        int gameId = std::stoi(gameIdStr);
        bool validGame = true;
        size_t startSetPos = idEndPos + 2;
        size_t endSetPos = line.find(';', startSetPos);
        std::string set = line.substr(startSetPos, endSetPos - startSetPos);
        size_t startPairPos = 0;

        // SETS in the game
        while (endSetPos != std::string::npos) {
          size_t endPairPos = set.find_first_of(';,');

          // PAIRS in the set
          while (startPairPos < set.length()) {
              size_t numberStartPos = startPairPos;
              size_t numberEndPos = set.find(' ', numberStartPos);
              int amount = std::stoi(set.substr(numberStartPos, numberEndPos - numberStartPos));
              size_t colorStartPos =  numberEndPos + 1;
              size_t colorEndPos = set.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", colorStartPos);
              std::string color = set.substr(colorStartPos, colorEndPos - colorStartPos);
              std::string pair = set.substr(numberStartPos, colorEndPos - numberStartPos);
              // // Check if amount exceeds the max for the color
              if ((color == "red" && amount > maxRed) ||
                  (color == "green" && amount > maxGreen) ||
                  (color == "blue" && amount > maxBlue)) {
                  validGame = false;
                  std::cout << "invalid game: " << gameId << std::endl;
                  break;
              }
              if (endPairPos == std::string::npos) {
                startPairPos = 0;
                break; // This was the last pair in the set
              }
              startPairPos = endPairPos + 2; // skip the , or ; and the space
              endPairPos = set.find_first_of(';,', startPairPos);
          }

          if (!validGame) {
            break;
          }

          startSetPos = endSetPos + 2; // skip semicolon and space
          if (startSetPos >= line.length()) {
            break;
          }

          endSetPos = line.find(';', startSetPos);
          if (endSetPos == std::string::npos) {
              endSetPos = line.length();
          }
          set = line.substr(startSetPos, endSetPos - startSetPos);
        }

        if (validGame) {
          sum += gameId;
        }

    }
    std::cout << "sum: " << sum << std::endl;
  }