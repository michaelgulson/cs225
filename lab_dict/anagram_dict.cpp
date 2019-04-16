/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::ifstream;
using std::string;
using std::vector;

void AnagramDict::sortTheWord(std::string theWord)
{
    //Because getthe word
    std::string getWOrd = theWord;

    //SOrt the word
    getWOrd = sortingThWOrd(getWOrd);

    //insert the word into the dict
    dict[getWOrd].push_back(theWord);
}

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string &filename)
{
    /* Your code goes here! */
    //OPen the file
    ifstream getTheWords;
    getTheWords.open(filename);
    //if(getTheWords.is_open() == true){
    //cout<< "is open << endl;
    //  }
    //Check to see if the data file is open
    if (getTheWords.is_open() == false)
    {
        return;
    }
    //if it is, then until the e of file, fill in the angram dict
    while (getTheWords.eof() == false)
    {
        std::string theWord;
        std::getline(getTheWords, theWord);
        //found this line online
        sortTheWord(theWord);
    }
    //while(std::getline)
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<std::string> &words)
{
    /* Your code goes here! */

    //found this line online
    //Just do what we did above.
    //Same as above, just easier because we dont have to open a file
    for (unsigned i = 0; i < words.size(); i++)
    {
        sortTheWord(words[i]);
    }
}

//Method for sorting the word
string AnagramDict::sortingThWOrd(std::string theWord) const
{
    std::string sortTOrd = theWord;
    std::sort(sortTOrd.begin(), sortTOrd.end());
    return sortTOrd;
}
/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const std::string &word) const
{
    /* Your code goes here! */
    //Use auto because TA said I could
    //find the word we want
    auto findVector = dict.find(sortingThWOrd(word));

    //CHeck to make sure the vector we got back is valid
    if (findVector == dict.end())
    {
        return vector<string>();
    }
    vector<string> returnVect = findVector->second;
    if (returnVect.size() < 2)
    {
        return vector<string>();
    }

    //If the vector is a valid vector, return it.
    return returnVect;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    //Because we already found one amagram, all we need to do is put it into a loop
    //and find anagram for all words.
    vector<vector<string>> theVectorOfVector;
    //Code to get all elements inside Dict
    for (auto inSideDIct : dict)
    {
        //for(int i = 0; i< dict.size(); i++){
        //std::string theWord = dict[i];

        //Since get_ana returns either an anagram, or an vector of nothing, only want the
        //anagram.
        if (get_anagrams(inSideDIct.first).size() < 1)
        {
        }
        else
        {

            //if anagram, push it back to vector of anagrams
            theVectorOfVector.push_back(get_anagrams(inSideDIct.first));
        }
    }

    //Make sure we are returning actually values
    if (theVectorOfVector.size() < 1)
    {
        return vector<vector<string>>();
    }

    //Return the vector if it has stuff in it.
    return theVectorOfVector;
}
