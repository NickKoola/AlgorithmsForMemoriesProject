#ifndef HAMMING_DISTANCE_H
#define HAMMING_DISTANCE_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <random>
#include <climits>

using std::vector;
using std::string;
using std::pair;
using std::unordered_map;
using std::min;


/**
 * @brief Brute-Force Approach. O(m^2 * n) time complexity.
 * best for small datasets.
 * @param m is the number of binary strings.
 * @param n is the length of the binary string.
 * 
 */
int hammingDistance(const string& a, const string& b);
pair<string, string> bruteForceClosestPair(const vector<std::string>& vectors);


/**
 * @brief MH LSH + Bitwise XOR Trick Approach. O(m*log(m)^2) avg time complexity.
 * Best for m >> n. 'n' up to 64.
 * @param m is the number of binary strings.
 * @param n is the length of the binary string.
 * 
 */
int hammingDistanceXOR(int a, int b);
int binaryStringToInteger(const string& bin);
vector<int> getRandomBitPositions(int length, int k, std::mt19937& gen);
string hashUsingPositions(const string& bin, const vector<int>& positions);
pair<string, string> multiHashLSHClosestPair(const vector<std::string>& vectors);

#endif // HAMMING_DISTANCE_H