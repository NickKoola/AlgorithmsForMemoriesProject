#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
class Word
{
    private:


        static int rand_word(int length);
        

        /**
         * @brief Converts a num to binary form with extended zeros according to length
         * in case log(num) > length, string would be truncated
         * 
         * @param num 
         * @param length 
         * @return std::string 
         */
        static std::string num_to_bin_string(int num,int length);

    public: 
        //decimal value of binary word
        unsigned int val;
        //bit size(taking into account zero extended binary sequences(001 != 1))
        size_t length;
        static unsigned int bin_pow(size_t length);  
        static int& getSeed();
        Word(){val = 0;length=0;};
        Word(size_t length):length(length),val(rand_word(length)){};
        Word(std::string str);
        Word(unsigned int val,size_t length):val(val),length(length){};
        ~Word();
        std::string getString() const;
        friend std::ostream& operator<<(std::ostream& os, const Word& word);
        //Performs a not operation on a single bit, given by index.
        bool flip(size_t index);
        //Pushes a given bit into the back of the word(LSB)
        void push_back(unsigned int bit);
        //Pushes a given bit into the front of the word(MSB)
        void push_front(unsigned int bit);
        //Pushes a given bit into a given index. The given index is the location of the pushed bit
        void push(unsigned int bit,size_t index);

        Word longest_common_sub_string(Word other);

        Word cut_suffix();
        Word cut_prefix();
        static Word longest_out_of4(Word word1,Word word2,Word word3,Word word4);
        static Word longest_common_sub_string_helper(Word first, Word second);
        //static Word recursiveLevenshteinDistance(Word word1,Word word2);
        
        
        


        
        bool operator<(const Word& other) const
        {
            if(other.val != val)
                return val < other.val;
            return length < other.length;
        }

        bool operator==(const Word& other) const
        {
            return length==other.length && val == other.val;
        }

        //Bitwise not operator would preserve bit length.
        Word operator~() const
        {
            unsigned int direct_not = ~val;
            return Word(direct_not%bin_pow(length),length);
        }

        //WARNING. [] operator returns a const val(non-modifiable)
        const unsigned int operator[](size_t index) const
        {
            //changed to msb being 0
            size_t modified_index = length-index-1;
            if(index >= length)
                return -1;
            return (val/bin_pow(modified_index)%2);
        }
};



