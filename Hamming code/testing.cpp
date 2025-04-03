#include "testing.hpp"


std::string generateRandomBinaryString(size_t bitLength, std::mt19937& gen) {

    std::bernoulli_distribution bit_dist(0.5); // 50% chance for 1
    std::string result;
    result.reserve(bitLength);
    for (size_t i = 0; i < bitLength; ++i) {
        result += bit_dist(gen) ? '1' : '0';
    }
    return result;
}

std::vector<std::string> generateRandomDataset(size_t setSize, size_t bitLength, std::mt19937& gen) {
    size_t maxUnique = 1ULL << bitLength; 
    if (setSize > maxUnique) {
        setSize = maxUnique; 
    }
    
    std::unordered_set<std::string> uniqueStrings;
    std::vector<std::string> dataset;
    dataset.reserve(setSize);

    std::bernoulli_distribution bit_dist(0.5);
    while (uniqueStrings.size() < setSize) {
        std::string newString;
        newString.reserve(bitLength);
        for (size_t i = 0; i < bitLength; ++i) {
            newString += bit_dist(gen) ? '1' : '0';
        }
        if (uniqueStrings.insert(newString).second) {
            dataset.push_back(newString);
        }
    }
    return dataset;
}

long long measureRunTime(HammingFunc func, const std::vector<std::string>& input) {
    func(input); // Warm-up
    auto start = std::chrono::high_resolution_clock::now();
    func(input);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}


std::vector<long long> collectRuntimes(HammingFunc func, int numRuns, std::vector<std::string>& dataset) {
    std::vector<long long> runtimes;
    runtimes.reserve(numRuns);
    for (int run = 0; run < numRuns; ++run) {
        runtimes.push_back(measureRunTime(func, dataset));
    }
    return runtimes;
}
std::pair<std::vector<long long>, std::vector<int>> collectRuntimesAndSuccess(
    HammingFunc func, int numRuns, const std::vector<std::string>& dataset, int trueMinDist
) {
    std::vector<long long> runtimes;
    std::vector<int> successes;
    runtimes.reserve(numRuns);
    successes.reserve(numRuns);

    for (int run = 0; run < numRuns; ++run) {
        auto start = std::chrono::high_resolution_clock::now();
        auto result = func(dataset);
        auto end = std::chrono::high_resolution_clock::now();
        long long runtime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        int dist = hammingDistance(result.first, result.second);
        bool success = (dist == trueMinDist);
        runtimes.push_back(runtime);
        successes.push_back(success ? 1 : 0);
    }
    return {runtimes, successes};
}

void saveRuntimesToCSV(const std::string& funcName, const std::vector<long long>& runtimes,
                       size_t setSize, size_t bitLength) {
    std::string filename = "results/" + funcName + "_setSize" + std::to_string(setSize) +
                           "_bitLength" + std::to_string(bitLength) + ".csv";
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    file << "Function," << funcName << "\n";
    file << "SetSize," << setSize << "\n";
    file << "BitLength," << bitLength << "\n";
    file << "Run,Time(us)\n";
    for (size_t i = 0; i < runtimes.size(); ++i) {
        file << i << "," << runtimes[i] << "\n";
    }
    file.close();
    std::cout << "Saved runtimes to " << filename << "\n";
}

void saveRuntimesAndSuccessToCSV(const std::string& funcName, const std::vector<long long>& runtimes,
                                 const std::vector<int>& successes, size_t setSize, size_t bitLength) {
    std::string filename = "results/" + funcName + "_setSize" + std::to_string(setSize) +
                           "_bitLength" + std::to_string(bitLength) + ".csv";
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    file << "Function," << funcName << "\n";
    file << "SetSize," << setSize << "\n";
    file << "BitLength," << bitLength << "\n";
    file << "Run,Time(us),Succeeded\n";
    for (size_t i = 0; i < runtimes.size(); ++i) {
        file << i << "," << runtimes[i] << "," << successes[i] << "\n";
    }
    file.close();
    std::cout << "Saved runtimes and success to " << filename << "\n";
}











