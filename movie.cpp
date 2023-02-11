#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
	Product(category, name, price, qty)
{
	category_ = category;
	name_ = name;
	price_ = price;
	qty_ = qty;
	genre_= genre;
	rating_=rating;
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const{
	std::set<std::string> keywords;
	typename std::set<std::string> nameset = parseStringToWords(name_);
	typename std::set<std::string>::iterator it;
	for(it = nameset.begin(); it != nameset.end(); ++it){
		keywords.insert(*it);
	}
	keywords.insert(convToLower(genre_));
	return keywords;
}

std::string Movie::displayString() const{
	stringstream ssconverter;
	ssconverter << price_ << " " << getQty();
	std::string price_string, qty_string;
	ssconverter >> price_string >> qty_string;
	std::string productinfo = name_+"\n"+"Genre: " + genre_ + " Rating: " + rating_ +"\n"+price_string+" "+qty_string+ " left.";
	return productinfo;
}

void Movie::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << getQty() << "\n" << genre_ <<"\n" << rating_<< endl;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
	
}