#include <iostream>
#include "Code.hpp"
#include <array>
#include "Export.hpp"

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

void check_levenshtein_dist()
{
    Word word1("01011101010001001");
    Word word2("01000101110000100");
    std::cout<< word1 << std::endl;
    std::cout<< word2 << std::endl;
    std::cout<< "distance : " << Code::levenshtein_dist(word1,word2) << std::endl;
}

void report_longest_common_substring()
{
    //trying verying lengths from 4 to 10
    //limiting size of
    std::vector<std::vector<int>> report; 
    std::vector<double> mean;
    long sum;
    for (size_t length = 4; length <= 20; length++)
    {
        std::cout<<"current length: " <<length<<std::endl;
        int pow = Word::bin_pow(length);
        size_t sample = pow/length;
        
        std::vector<int> current_length_results;
        sum = 0;
        for (size_t j = 0; j < (length > 8 ? sample : sample); j++)
        {
            std::cout << "\rcurrent length: " << length << " current sample: " << j << " out of :" << sample << std::flush;
            Word first(length);
            Word second(length);
            int res = (first.longest_common_sub_string(second)).length;
            sum += res;
            current_length_results.push_back(res);
        }
        report.push_back(current_length_results);
        mean.push_back(sum/(double)sample);
    }
    std::cout<<"alllegedly built csv" <<std::endl;
    //exportToCSV("substring_report",report);
    std::vector<std::vector<double>> mean_report;
    mean_report.push_back(mean);
    exportToCSV("mean_substring_report3",mean_report);
    
}

double check_exact_longest_sub_string_mean(int n)
{
    std::vector<Word> full_words_set;
    std::cout << "n is " << n <<std::endl;
    int total_size = Word::bin_pow(n);
    int sum = 0;
    std::cout << "total words count is " << total_size <<std::endl;
    for (size_t i = 0; i < total_size; i++)
    {
        full_words_set.push_back(Word(i,n));
    }
  
    size_t i = 0;
       
        Word current_word =full_words_set.at(i);
        for (size_t j = 0; j < total_size; j++)
        {
            if(i !=j)
                {
                    Word current_comapre = full_words_set.at(j);
                   
                    Word res = current_word.longest_common_sub_string(current_comapre);
                    sum+= res.length;
                }
                
        }
        
    
    return (double)sum/(total_size - 1);
}

void list_exeact_lcss_mean()
{
    for (size_t i = 4; i < 6; i++)
    {
        int res = check_exact_longest_sub_string_mean(i);
        std::cout <<"exact lcss mean for n=" << i<< " is: " <<res <<std::endl;
    }

}

int stringRecursiveLevenshteinDistance(const std::string& A, const std::string& B) {
    // Base cases: one of the strings is empty
    
    
    if (A.empty()) return B.size();
    if (B.empty()) return A.size();
    std::cout<< "called pair (" << A <<"," << B <<")" << std::endl;
    // Check first character
    int cost = (A[0] == B[0]) ? 0 : 1;

    // Recursive calls for insert, delete, and substitute
    return std::min({
        stringRecursiveLevenshteinDistance(A.substr(1), B) + 1,        // Delete A[0]
        stringRecursiveLevenshteinDistance(A, B.substr(1)) + 1,        // Insert B[0]
        stringRecursiveLevenshteinDistance(A.substr(1), B.substr(1)) + cost // Substitute A[0] -> B[0]
    });
}

int DPlevenshteinDistance(const string &A, const string &B) {
    int m = A.size(), n = B.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
 
    for (int i = 0; i <= m; i++) dp[i][0] = i;

    for (int j = 0; j <= n; j++) dp[0][j] = j;  

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (A[i - 1] == B[j - 1]) ? 0 : 1;
            dp[i][j] = min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1,dp[i - 1][j - 1] + cost 
            });
        }
    }
    return dp[m][n];  
}

int ukkonenLevenshteinDistance(const string& A, const string& B, int k) {
    int m = A.size();
    int n = B.size();
    
    vector<vector<int>> dp(2, vector<int>(n + 1, 0));
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= m; i++) {
        int curr = i % 2;
        int prev = (i - 1) % 2;

        for (int j = max(0, i - k); j <= min(n, i + k); j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[curr][j] = dp[prev][j - 1];
            } else {
                dp[curr][j] = min({dp[prev][j] + 1,    dp[curr][j - 1] + 1,   dp[prev][j - 1] + 1});  
            }
        }
    }
    return dp[m % 2][n];
}

int main(int argc, char const *argv[])
{
    //dont remove
    Word::getSeed();
   //print_rand_word_test();
   //check_bin_power();
   //check_index_function();
   //check_flip();
   //check_push_back_front();
   //check_levenshtein_dist();
   //list_exeact_lcss_mean();
   //report_longest_common_substring();
   std::cout << stringRecursiveLevenshteinDistance("dog","do");
    return 0;
}

using namespace std;



