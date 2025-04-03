#include "HammingDistance.hpp"


// Brute-Force Approach:
int hammingDistance(const string& a, const string& b) {  //use when n(bitLength) is >= 32
    int distance = 0;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) distance++;
    }
    return distance;
}

pair<string, string> bruteForceClosestPair(const vector<string>& binaryStrings) {
    int minDist = INT_MAX;
    pair<string, string> closestPair;

    for (size_t i = 0; i < binaryStrings.size(); i++) {
        for (size_t j = i + 1; j < binaryStrings.size(); j++) {
            int currDist = hammingDistance(binaryStrings[i], binaryStrings[j]);
            if (currDist < minDist) {
                minDist = currDist;
                closestPair = {binaryStrings[i], binaryStrings[j]};
            }
        }
    }

    return closestPair;
}
// End of Brute-Force Approach.

// Multi-Hash LSH Closest Pair
int hammingDistanceXOR(int x, int y) {
    return __builtin_popcount(x ^ y); // Count the number of 1s in the binary representation of xorResult
}

int binaryStringToInteger(const string& binaryString) {
    return stoi(binaryString, nullptr, 2);
}

vector<int> getRandomBitPositions(int length, int k, std::mt19937& gen) {

    vector<int> positions(length);
    iota(positions.begin(), positions.end(), 0);
    shuffle(positions.begin(), positions.end(), gen);
    return vector<int>(positions.begin(), positions.begin() + k);
}

string hashUsingPositions(const string& bin, const vector<int>& positions) {
    string hash;
    hash.reserve(positions.size());
    for (int pos : positions) {
        hash += bin[pos];
    }
    return hash;
}

pair<string, string> multiHashLSHClosestPair(const vector<string>& vectors) {
    if (vectors.empty() || vectors.size() < 2) return {"", ""};

    const size_t m = vectors.size();
    const size_t n = vectors[0].length();

    const int k = std::max(1, static_cast<int>(std::log2(m)));  // Bits per hash
    const int L = std::max(1, static_cast<int>(std::log2(m)));  // Hash repetitions

    size_t minDist = n + 1;  // Max possible hamming dist + 1
    pair<string, string> closestPair = {vectors[0], vectors[1]};

    std::random_device rd;
    std::mt19937 gen(rd());

    // L repetitions of LSH
    for (int rep = 0; rep < L; ++rep) {
        vector<int> bitPositions = getRandomBitPositions(n, k, gen);
        unordered_map<string, vector<string>> buckets;

        // Hash vectors into buckets
        for (const auto& str : vectors) {
            string key = hashUsingPositions(str, bitPositions);
            buckets[key].push_back(str);
        }

        // Process each bucket
        for (const auto& [key, bucket] : buckets) {
            if (bucket.size() < 2) continue;  // Skip buckets with 1 or fewer items
            vector<int> intBucket;
            intBucket.reserve(bucket.size());
            for (const auto& str : bucket) {
                intBucket.push_back(binaryStringToInteger(str));
            }

            for (size_t i = 0; i < intBucket.size(); ++i) {
                for (size_t j = i + 1; j < intBucket.size(); ++j) {
                    size_t dist = hammingDistanceXOR(intBucket[i], intBucket[j]);
                    if (dist < minDist) {
                        minDist = dist;
                        closestPair = {bucket[i], bucket[j]};
                    }
                }
            }
        }
    }

    return closestPair;
}

