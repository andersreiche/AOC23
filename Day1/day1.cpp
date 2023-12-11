#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // for isdigit

int main() {
    // Open a file for reading
    std::ifstream file("puzzleInput.txt");

    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Unable to open the file" << std::endl;
        return 1; // return an error code
    }

    // Read the file line by line
    std::string line;
    uint64_t sum = 0;
    while (std::getline(file, line)) {
        // Process each line as needed
        int lhs = -1;
        int rhs = -1;
        for (auto c: line) {
            if (isdigit(c)) {
                if (lhs == -1) {
                    lhs = c - '0'; // conversion from ascii to integer
                }
                rhs = c - '0'; // conversion from ascii to integer
            }
        }
        sum += (10 * lhs) + rhs;
        std::cout << sum << std::endl;
    }
    // Close the file
    file.close();
    std::cout << sum << std::endl;

    return 0;
}
