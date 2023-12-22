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

struct {
  uint64_t source;
  uint64_t destination;
  uint64_t length;
} map_entry;

// k: source, v: destination
std::unordered_map<uint64_t, uint64_t> seed_to_soil;
std::unordered_map<uint64_t, uint64_t> soil_to_fertilizer;
std::unordered_map<uint64_t, uint64_t> fertilizer_to_water;
std::unordered_map<uint64_t, uint64_t> water_to_light;
std::unordered_map<uint64_t, uint64_t> light_to_temperature;
std::unordered_map<uint64_t, uint64_t> temperature_to_humidity;
std::unordered_map<uint64_t, uint64_t> humidity_to_location;

enum MapType { 
  SEED_TO_SOIL, 
  SOIL_TO_FERTILIZER, 
  FERTILIZER_TO_WATER,
  WATER_TO_LIGHT,
  LIGHT_TO_TEMPERATURE,
  TEMPERATURE_TO_HUMIDITY,
  HUMIDITY_TO_LOCATION,
  UNKNOWN,
};

enum ParseType { 
  NUMBERS,
  TEXT,
};

void parseMaps(MapType maptype, ParseType parsetype) {
  
}

uint64_t run() {
  std::vector<int> seeds;
  MapType maptype = UNKNOWN;
  ParseType parsetype = TEXT;
  uint64_t result = 0;
  std::ifstream file("testInput.txt");
  std::string line;
  std::getline(file, line);
  std::string tmp; 
  std::istringstream iss(line);
  iss >> tmp;
  uint64_t num = 0;
  while (iss >> num) {
      seeds.push_back(num);
  }
  while (std::getline(file, line)) {
    if (line == "") {
      parsetype = TEXT;
      continue;
    }
    parseMaps(maptype, parsetype);
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