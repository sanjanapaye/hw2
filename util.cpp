#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keywords;
    stringstream ss(rawWords);
    string word;
    while(ss >> word){
        bool haspunct = false;
        int splitindex = 0;
        for(size_t i = 0; i < word.size(); ++i){
            if(ispunct(word[i])!=0){
                haspunct = true;
                splitindex = i;
            }
        }
        if (haspunct == true){
            stringstream ss2;
            for(int i = 0; i < splitindex; ++i){
                ss2 << word[i];
            }
            ss2 << " ";
            for(size_t i = (splitindex+1); i<word.size(); ++i){
                ss2 << word[i];
            }
            string word1, word2;
            ss2 >> word1;
            if(word1.size()>=2){
                keywords.insert(convToLower(word1));
            }
            ss2 >> word2;
            if(word2.size()>=2){
                keywords.insert(convToLower(word2));
            }
        }else{
            keywords.insert(convToLower(word));
        }
    }
    return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
