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

struct Map_Entry {
  uint64_t destination;
  uint64_t source;
  uint64_t length;

  Map_Entry(uint64_t dest, uint64_t src, uint64_t len) : destination(dest), source(src), length(len) {}
};

std::vector<Map_Entry> seed_to_soil;
std::vector<Map_Entry> soil_to_fertilizer;
std::vector<Map_Entry> fertilizer_to_water;
std::vector<Map_Entry> water_to_light;
std::vector<Map_Entry> light_to_temperature;
std::vector<Map_Entry> temperature_to_humidity;
std::vector<Map_Entry> humidity_to_location;

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

uint64_t getLocationFromSeed(uint64_t seed) {
  uint64_t x = seed;
  for (const auto& entry : seed_to_soil) { 
    if (x >= entry.source && x < entry.source + entry.length) {
      x = entry.destination + (x - entry.source);
      break;
    }
  }
  for (const auto& entry : soil_to_fertilizer) { 
    if (x >= entry.source && x < entry.source + entry.length) {
      x = entry.destination + (x - entry.source);
      break;
    }
  }
  for (const auto& entry : fertilizer_to_water) { 
    if (x >= entry.source && x < entry.source + entry.length) {
      x = entry.destination + (x - entry.source);
      break;
    }
  }
  for (const auto& entry : water_to_light) { 
    if (x >= entry.source && x < entry.source + entry.length) {
      x = entry.destination + (x - entry.source);
      break;
    }
  }
  for (const auto& entry : light_to_temperature) { 
    if (x >= entry.source && x < entry.source + entry.length) {
      x = entry.destination + (x - entry.source);
      break;
    }
  }
  for (const auto& entry : temperature_to_humidity) { 
    if (x >= entry.source && x < entry.source + entry.length) {
      x = entry.destination + (x - entry.source);
      break;
    }
  }
  for (const auto& entry : humidity_to_location) { 
    if (x >= entry.source && x < entry.source + entry.length) {
      x = entry.destination + (x - entry.source);
      break;
    }
  }
  return x;
}

void parseMaps(MapType maptype, std::string input) {
  std::istringstream iss(input);
  uint64_t destination, source, length;
  iss >> destination >> source >> length;
  switch (maptype)
  {
  case SEED_TO_SOIL:
    seed_to_soil.push_back(Map_Entry(destination, source, length));
    break;
  case SOIL_TO_FERTILIZER:
    soil_to_fertilizer.push_back(Map_Entry(destination, source, length));
    break;
  case FERTILIZER_TO_WATER:
    fertilizer_to_water.push_back(Map_Entry(destination, source, length));
    break;
  case WATER_TO_LIGHT:
    water_to_light.push_back(Map_Entry(destination, source, length));
    break;
  case LIGHT_TO_TEMPERATURE:
    light_to_temperature.push_back(Map_Entry(destination, source, length));
    break;
  case TEMPERATURE_TO_HUMIDITY:
    temperature_to_humidity.push_back(Map_Entry(destination, source, length));
    break;
  case HUMIDITY_TO_LOCATION:
    humidity_to_location.push_back(Map_Entry(destination, source, length));
    break;
  default:
    std::cout << "Unknown maptype: " << maptype << std::endl;
    break;
  }
}

uint64_t run() {
  std::vector<int> seeds;
  MapType maptype = UNKNOWN;
  ParseType parsetype = TEXT;
  uint64_t result = UINT64_MAX;
  std::ifstream file("puzzleInput.txt");
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
    if (parsetype == TEXT) {
      if (line == "seed-to-soil map:") { maptype = SEED_TO_SOIL; }
      else if (line == "soil-to-fertilizer map:") { maptype = SOIL_TO_FERTILIZER; }
      else if (line == "fertilizer-to-water map:") { maptype = FERTILIZER_TO_WATER; }
      else if (line == "water-to-light map:") { maptype = WATER_TO_LIGHT; }
      else if (line == "light-to-temperature map:") { maptype = LIGHT_TO_TEMPERATURE; }
      else if (line == "temperature-to-humidity map:") { maptype = TEMPERATURE_TO_HUMIDITY; }
      else if (line == "humidity-to-location map:") { maptype = HUMIDITY_TO_LOCATION; }
      parsetype = NUMBERS;
      continue;
    } else {
      parseMaps(maptype, line);
    }
    
  }
  for (const auto& seed : seeds) { 
    uint64_t location = getLocationFromSeed(seed);
    result = (location < result) ? location : result;
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