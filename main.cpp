/*
#include <iostream>
#include "Code.hpp"

void check_index_function()
{
    Word word1(8,8);
    Word word2(16,8);
    Word word3(32,8);
    std::cout<< word1 << std::endl;
    std::cout<<"bit at " << 3 << " is " <<word1[3]<< std::endl;
    std::cout<< word2 << std::endl;
    std::cout<<"bit at " << 4 << " is " <<word2[4]<< std::endl;
    std::cout<< word3 << std::endl;
    std::cout<<"bit at " << 5 << " is " <<word3[5]<< std::endl;
    std::cout<<"bit at " << 6 << " is " <<word3[6]<< std::endl;
}
void print_rand_word_test()
{
    Code code(5);
    
    for (size_t i = 0; i < 4; i++)
    {
        code.add_word();
    }

    for (auto i = code.words.begin(); i != code.words.end(); i++)
    {
        std::cout<< *i << std::endl;
    }
}

void check_bin_power()
{
    std::cout<< " displaying powers of 2" <<std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout<< Word::bin_pow(i)<< std::endl;
    }
    
}

void check_flip()
{
    Word word1(7,8);
    Word word2(0,8);
    Word word3(0,8);
    std::cout<< word1 << std::endl;
    word1.flip(0);
    std::cout<<"flipped 0: " << word1<< std::endl;
    std::cout<< word2 << std::endl;
    word2.flip(2);
    std::cout<<"flipped 2: " << word2<< std::endl;
    std::cout<< word3 << std::endl;
    word3.flip(4);
    std::cout<<"flipped 4: " << word3<< std::endl;
}

void check_not()
{
    Word word1(8,8);
    Word word2(16,8);
    Word word3(26,8);
    std::cout<< word1 << std::endl;
    std::cout<<"flipped: " << ~word1<< std::endl;
    std::cout<< word2 << std::endl;
    std::cout<<"flipped: " << ~word2<< std::endl;
    std::cout<< word3 << std::endl;
    std::cout<<"flipped: " << ~word3<< std::endl;
}

void check_push_back_front()
{
    Word word1(8,5);
    Word word2(11,5);
    Word word3(12,5);

    std::cout<< "invoking bad push: " <<std::endl;
    try
    {
        word1.push_back(2);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    std::cout<< word1 << std::endl;
    word1.push_back(1);
    std::cout<<"pushed back 1: " << word1<< std::endl;

    std::cout<< word2 << std::endl;
    word2.push_front(1);
    std::cout<<"pushed front 1: " << word2<< std::endl;

    std::cout<< word3 << std::endl;
    word3.push_back(0);
    std::cout<<"pushed back 0: " << word3<< std::endl;
}

void check_push()
{
    Word word1(0,4);
    std::cout<< word1 << std::endl;
    std::cout<< "push 1 at 3" << std::endl;
    word1.push(1,3);
    std::cout<< word1 << std::endl;

    std::cout<< "push 1 at 0" << std::endl;
    word1.push(1,0);
    std::cout<< word1 << std::endl;
    
    std::cout<< "push 0 at 4" << std::endl;
    word1.push(0,4);
    std::cout<< word1 << std::endl;

}
*/

#include "HammingDistance.hpp"
#include "testing.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <filesystem>


int main() {
    std::cout << "Hello, World!" << std::endl;
    try {
        std::filesystem::create_directory("results");
        std::cout << "Created results directory.\n";

        // Test parameters
        size_t bitLength = 20;
        std::vector<size_t> setSizes = {250, 500, 1000, 2500, 5000, 10000}; 
        int numRuns = 5;  // Number of runs per test

        std::cout << "Starting tests...\n";
        for (size_t setSize : setSizes) {
            // Generate a single dataset for consistency across runs
            std::random_device rd;
            std::mt19937 gen(rd());
            std::vector<std::string> dataset = generateRandomDataset(setSize, bitLength, gen);

            // Run brute-force once to get the ground truth
            std::cout << "  Running bruteForce for setSize " << setSize << "...\n";
            auto bruteForceResult = bruteForceClosestPair(dataset);
            int trueMinDist = hammingDistance(bruteForceResult.first, bruteForceResult.second);
            auto bruteForceRuntimes = collectRuntimes(bruteForceClosestPair, numRuns, dataset);
            saveRuntimesToCSV("bruteForce", bruteForceRuntimes, setSize, bitLength);

            // Run multi-hash LSH and compare to brute-force result
            std::cout << "  Running multiHashLSH for setSize " << setSize << "...\n";
            auto [lshRuntimes, lshSuccesses] = collectRuntimesAndSuccess(
                multiHashLSHClosestPair, numRuns, dataset, trueMinDist
            );
            saveRuntimesAndSuccessToCSV("multiHashLSH", lshRuntimes, lshSuccesses, setSize, bitLength);
        }

        std::cout << "Testing completed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}



    /*
    //dont remove
    Word::getSeed();
    //print_rand_word_test();
    //check_bin_power();
    //check_index_function();
    //check_flip();
    //check_push_back_front();
    check_push();
    */


