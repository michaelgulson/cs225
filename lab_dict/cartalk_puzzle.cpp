/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    vector<std::string> words_vec;

    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open())
    {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word))
        {
            //words_vec.push_back(word);
            if(word.size()<3){
                continue;
            }
            string currString, subString1, subString2;
            currString = word;
            //wrack -> rack
            //[pos,size()]
            //std::str.substr(1);
            subString1 = currString.substr(1);

            //wrack -> wack
            //substring2 std::str.substr(2);
            //std::str.insert(0, substring2)
            subString2 = currString.substr(2);
            subString2 = subString2.insert(0, 1, currString[0]);

            if (d.homophones(subString1, subString2) && d.homophones(currString, subString2))
            {
                ret.emplace_back(currString, subString1, subString2);
            }
        }
    }

    //wrack -> rack
    //[pos,size()]
    //std::str.substr(1);

    // for (size_t i = 0; i < words_vec.size(); i++)
    // {
        

    // }
    


    return ret;
}
