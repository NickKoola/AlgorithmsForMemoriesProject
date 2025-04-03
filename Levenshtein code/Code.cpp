#include "Code.hpp"

bool Code::add_word()
{
    if(words.size() >= Word::bin_pow(length))
        return false;
  
         while (!words.insert(Word(length)).second){}    
    return true;
}

bool Code::add_word(Word word)
{
    
    return words.insert(word).second;
}
bool Code::add_word(unsigned int val,size_t length)
{
    return words.insert(Word(val,length)).second;
}

//notice indices are reveresed as to a conventional string
 int Code::levenshtein_dist(Word word1, Word word2)
{
    if(word1.length == 0)
        return word2.length;
    else if(word2.length == 0)
        return word1.length;

    Word cut_word1(word1.val/2,word1.length-1);
    Word cut_word2(word2.val/2,word2.length-1);
    if(word1[0] == word2[0])
    {
            return levenshtein_dist(cut_word1,cut_word2);
    }

    int res1 = levenshtein_dist(cut_word1,word2);
    int res2 = levenshtein_dist(word1,cut_word2);
    int res3 = levenshtein_dist(cut_word1,cut_word2);

    if(res1 < res2)
        if(res1 < res3)
            return 1 + res1;
        else
            return 1 + res3;
    if(res2 < res3)
        return 1 + res2;
    else 
        return 1 + res3;
    
  
}

void Code::FILL_CODE()
{
    words.empty();
    int total_size = Word::bin_pow(length);
    for (size_t i = 0; i < total_size; i++)
    {
        words.insert(Word(i,length));
    }
    
}

Code::~Code()
{
}
