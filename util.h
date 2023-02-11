#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> intersection;
	std::set<T> firstset = s1;
	std::set<T> secondset = s2;
	typename std::set<T>::iterator it;
	for(it = firstset.begin() ; it != firstset.end(); ++it){
		if(secondset.find(*it) != secondset.end()){
			intersection.insert(*it);
		}
	}
	return intersection;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> union1;
	std::set<T> firstset = s1;
	std::set<T> secondset = s2;
	typename std::set<T>::iterator it;
	for(it = firstset.begin(); it != firstset.end(); ++it){
		union1.insert(*it);
	}
	for(it = secondset.begin() ; it != secondset.end(); ++it){
		if(union1.find(*it) == union1.end()){
			union1.insert(*it);
		}
	}
	return union1;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
