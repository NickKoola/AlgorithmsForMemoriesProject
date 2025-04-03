#include "Word.hpp"

int Word::rand_word(int length)
{
    return rand()%bin_pow(length);   
}

unsigned int Word::bin_pow(size_t length)
{
    return 1<<length;
}
std::string Word::getString() const
{
    return num_to_bin_string(val,length);
}
std::string Word::num_to_bin_string(int num,int length)
{
    std::string current = "";
    for (size_t i = 0; i < length; i++)
    {
        current = std::to_string(num%2) + current;
        num = num/2;
    }
    return current;
    
}

int& Word::getSeed()
{
    static int seed;
    seed = static_cast<int>(std::time(nullptr)); // Generate seed
    std::srand(seed); 
    return seed;
}

std::ostream& operator<<(std::ostream& os, const Word& word) {
    os << word.getString(); // Convert to std::string
    return os;
}

bool Word::flip(size_t index)
{
    if(index >= length)
        return false;
    unsigned int power = bin_pow(index);
    unsigned int flipped_bit = 1 - (*this)[index];
    if(flipped_bit)
        val += power;
    else
        val-= power;
    return true;
}

void Word::push_back(unsigned int bit)
{
    if(bit >= 2)
        throw std::invalid_argument("non bit value given");
    //adjust size
    length++;
    //shift
    val = val << 1;
    //determine first bit
    val += bit;
}
void Word::push_front(unsigned int bit)
{
    if(bit >= 2)
     throw std::invalid_argument("non bit value given");

    //zero bit woudl'nt change val
    if(bit)
        val += bin_pow(length);
    length++;
}

void Word::push(unsigned int bit,size_t index)
{
    if(index >= length)
        throw std::invalid_argument("out of bounds index");
    if(bit >= 2)
        throw std::invalid_argument("non binary value bit");
    //Splitting the val to gap created by push
    unsigned int pre_index_val = val%bin_pow(index);
    unsigned int post_index_val = val - pre_index_val;
    unsigned int shifted_bit = bit << index;
    //post_index | new bit | pre_index
    val = (post_index_val << 1) + shifted_bit + pre_index_val;
    length ++;
}

Word::Word(std::string str)
{
    length = str.size();
    int pow = 1;
    val = 0;
    for (size_t i = 0; i < length; i++)
    {
        if(str.at(length-i-1) == '1')
            val+= pow;
        pow *=2; 
    }
    
}

Word Word::longest_common_sub_string(Word other)
{
    return longest_common_sub_string_helper(*this,other);
}

static std::unordered_map<std::string, Word> memo;

static std::string getKey(const Word& first, const Word& second) {
    return std::to_string(first.val) + "," + std::to_string(first.length) + "," + std::to_string(second.val) + "," + std::to_string(second.length);
}

Word Word::longest_common_sub_string_helper(Word first, Word second)
{
    // Base cases
    if(first.length == 0 || second.length == 0)
        return Word(0, 0);
    if(first == second)
        return first;
    
    // Check if the result is already in memo
    std::string key = getKey(first, second);
    if (memo.find(key) != memo.end()) {
        return memo[key];  // Return the cached result
    }
    
    Word result;
    
    if(first.length > second.length) {
        Word first_prefix = longest_common_sub_string_helper(first.cut_prefix(), second);
        Word first_suffix = longest_common_sub_string_helper(first.cut_suffix(), second);
        result = (first_prefix.length > first_suffix.length) ? first_prefix : first_suffix;
    } else if(first.length < second.length) {
        Word second_prefix = longest_common_sub_string_helper(first, second.cut_prefix());
        Word second_suffix = longest_common_sub_string_helper(first, second.cut_suffix());
        result = (second_prefix.length > second_suffix.length) ? second_prefix : second_suffix;
    } else {
        Word first_prefix = longest_common_sub_string_helper(first.cut_prefix(), second);
        Word first_suffix = longest_common_sub_string_helper(first.cut_suffix(), second);
        Word second_prefix = longest_common_sub_string_helper(first, second.cut_prefix());
        Word second_suffix = longest_common_sub_string_helper(first, second.cut_suffix());
        result = longest_out_of4(first_prefix, first_suffix, second_prefix, second_suffix);
    }

    // Store the result in the memoization cache
    memo[key] = result;
    
    return result;
}

//suffix is lsb
Word Word::cut_suffix()
{
    if(length > 0)
    {
        val = val/2;
        length--;
    }
    return *this;

}
//prefix is msb
Word Word::cut_prefix()
{
    if(length > 0)
    {
        length--;
        int pow = bin_pow(length);
        if(val > pow)
            val = val % pow;
    }
    

    return *this;
}

Word Word::longest_out_of4(Word word1, Word word2, Word word3, Word word4)
{
    int lengthest = std::max({word1.length, word2.length, word3.length, word4.length});

    if (word1.length == lengthest)
        return word1;
    else if (word2.length == lengthest)
        return word2;
    else if (word3.length == lengthest)
        return word3;
    else
        return word4;
}



Word::~Word()
{
}