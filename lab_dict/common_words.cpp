/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        for(unsigned long j = 0; j < words.size(); j++){
           // auto lookup_file_word_maps = file_word_maps[i].find(words[j]);
            //if (lookup_file_word_maps != file_word_maps[i].end()){
                //lookup_file_word_maps = words[i];
                //(file_word_maps[i])[j]->second = ;
                
                //???this is buggy too
                //++lookup_file_word_maps->second;

                //???I don't understand how this works
                file_word_maps[i][words[j]]++;
            //}
            /*else{
                //add word to file_word_maps
                file_word_maps[i].insert({words[i], 0});
            }*/
        }
    }


    // ////////////FOR DEBUGGING REMEMBER TO COMMENT OUT//////////////////

    // auto file_word_maps_itr = file_word_maps.begin();
    // cout << file_word_maps.size() << endl;
    // for (size_t i = 0; i < filenames.size(); i++)
    // {
    //     auto file_word_maps_itr = file_word_maps[i].begin();
    //     for (file_word_maps_itr = file_word_maps[i].begin(); file_word_maps_itr != file_word_maps[i].end(); file_word_maps_itr++)
    //     {
    //         cout << (*file_word_maps_itr).first << (*file_word_maps_itr).second << endl;
    //     }
    //     ///////////////////////////////////////////////////////////////
    // }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
//iterate througgh files

    for(unsigned long i = 0; i < file_word_maps.size(); i++)
    { //iterate througgh files
        auto lookup_file_word_maps = (file_word_maps[i]).begin();
        for (lookup_file_word_maps = (file_word_maps[i]).begin(); lookup_file_word_maps != (file_word_maps[i]).end(); lookup_file_word_maps++){
            auto lookup_common = common.find((*lookup_file_word_maps).first);
            // if (lookup_common == file_word_maps[i].end())
            // {
                //file_word_maps[i][words[j]]++;
            // common.insert(*(lookup_file_word_maps));
                // common[file_word_maps[i].first]++;
            if (lookup_common != (file_word_maps[i]).end())
            {
                (*lookup_common).second++;
            }
            //DNE
            else{
                common[(*lookup_file_word_maps).first] = 1;
                //common.insert({lookup_file_word_maps->first, 1});
            }
            // }
            // else{
            //     //do nothing?
            //     //common.insert({lookup_file_word_maps->first, 1});
            //     lookup_common->second = lookup_common->second + lookup_file_word_maps->second;
            // }
        }

    }


    for (auto &file_word_map_ : file_word_maps)
    {
        for (auto &key : file_word_map_)
        {
            common[key.first]++;
        }
    }

    // ////////////FOR DEBUGGING REMEMBER TO COMMENT OUT//////////////////
    // auto common_itr = common.begin();
    // cout<< common.size() <<endl;
    // for (common_itr = common.begin(); common_itr != common.end(); common_itr++)
    // {
    //     cout << (*common_itr).first << (*common_itr).second << endl;
    // }
    // /////////////////////////////////////////////////////////////////////////
}
/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    // vector<string> out;
    // /* Your code goes here! */

    // // for (unsigned long i = 0; i < file_word_maps.size(); i++)
    // // {
    // //     auto lookup_file_word_maps = (file_word_maps[i]).begin();
    // //     for (lookup_file_word_maps = (file_word_maps[i]).begin(); lookup_file_word_maps != (file_word_maps[i]).end(); lookup_file_word_maps++)
    // //     {
    // //         if(lookup_file_word_maps->second >= n){
    // //             out.push_back(lookup_file_word_maps->first);
    // //         }
    // //     }
    // // }

    // auto lookup_common = common.begin();
    // for (lookup_common = common.begin(); lookup_common != common.end(); lookup_common++)
    // {
    //     if ((*lookup_common).second >= n)
    //     {
    //         out.push_back((*lookup_common).first);
    //     }
    // }

    // return out;


    ////geeeeeetheeeebcceeeedddd

    vector<string> out;
    for (auto &k_v : common)
    { //common: string -> uint
        if (k_v.second == file_word_maps.size())
        {
            bool pass = true;
            for (auto map : file_word_maps)
            { //map: string -> uint, word -> count, per file
                if (map[k_v.first] < n)
                {
                    pass = false;
                    break;
                }
            }
            if (pass)
            {
                out.push_back(k_v.first);
            }
        }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
