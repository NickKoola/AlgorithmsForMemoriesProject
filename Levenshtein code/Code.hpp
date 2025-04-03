#include "Word.hpp"
#include <set>
class Code
{
private:
    int length;
public:
    std::set<Word> words;

    Code(int length):length(length){};
    Code(){};
    //Adds a random word. Legnth of new word determined by Code class defined length
    bool add_word();
    //Adds a given word into Code. Allows word in different length than defined at Code
    bool add_word(Word word);
    bool add_word(unsigned int val,size_t length);
    static int levenshtein_dist(Word word1, Word word2);
    //heavy operation. fills class with all possible words lengthed n
    void FILL_CODE();
    ~Code();
};

