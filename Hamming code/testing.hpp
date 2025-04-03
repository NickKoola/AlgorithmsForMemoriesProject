#ifndef TESTING_HPP
#define TESTING_HPP

#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <fstream>
#include <unordered_set>
#include "HammingDistance.hpp"

using HammingFunc = std::pair<std::string, std::string>(*)(const std::vector<std::string>&);

std::string generateRandomBinaryString(size_t bitLength, std::mt19937& gen);
std::vector<std::string> generateRandomDataset(size_t setSize, size_t bitLength, std::mt19937& gen);
long long measureRunTime(HammingFunc func, const std::vector<std::string>& input);
std::vector<long long> collectRuntimes(HammingFunc func, int numRuns, std::vector<std::string>& dataset);
std::pair<std::vector<long long>, std::vector<int>> collectRuntimesAndSuccess(
    HammingFunc func, int numRuns, const std::vector<std::string>& dataset, int trueMinDist
);
void saveRuntimesToCSV(const std::string& funcName, const std::vector<long long>& runtimes, size_t setSize, size_t bitLength);
void saveRuntimesAndSuccessToCSV(const std::string& funcName, const std::vector<long long>& runtimes,
                                 const std::vector<int>& successes, size_t setSize, size_t bitLength);
#endif
