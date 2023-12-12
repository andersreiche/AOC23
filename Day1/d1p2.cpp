#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // for isdigit
#include <unordered_map>

std::unordered_map<std::string, int> numberMap;

int main() {
    numberMap["one"] = 1;
    numberMap["two"] = 2;
    numberMap["three"] = 3;
    numberMap["four"] = 4;
    numberMap["five"] = 5;
    numberMap["six"] = 6;
    numberMap["seven"] = 7;
    numberMap["eight"] = 8;
    numberMap["nine"] = 9;

    std::ifstream file("puzzleInput.txt");

    std::string line;
    uint64_t sum = 0;
    while (std::getline(file, line)) {
        // Process each line as needed
        int lhs = -1;
        int rhs = -1;

        // Iterate through the characters in the line
        size_t lineLength = line.length();
        for (size_t i = 0; i < lineLength; ++i) {
            // Check if the character is a digit
            if (isdigit(line[i])) {
                if (lhs == -1) {
                    lhs = line[i] - '0';
                }
                rhs = line[i] - '0';
            } else {
                // Check each key in the numberMap
               for (const auto& kv : numberMap) {
                  const std::string& key = kv.first;
                  size_t keyLength = key.length();
                  // Check if the current position i allows extracting a substring of key's length
                  if (i + keyLength <= lineLength) {
                      std::string substr = line.substr(i, keyLength);

                      // If the extracted substring matches the key, update lhs and rhs
                      if (substr == key) {
                          if (lhs == -1) {
                              lhs = kv.second;
                          }
                          rhs = kv.second;
                          i ++; // Move the iterator to the end of the key
                          break;
                      }
                  }
              }
            }
        }
        sum += (10 * lhs) + rhs;
        std::cout << (10 * lhs) + rhs << std::endl;
    }

    // Close the file
    file.close();
    std::cout << "sum: " << sum << std::endl;

    return 0;
}