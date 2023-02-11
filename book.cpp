#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author): Product(category, name, price, qty)
{
	category_ = category;
	name_ = name;
	price_ = price;
	qty_ = qty;
	ISBN_ = ISBN;
	author_ = author;
}

Book::~Book()
{

}


std::set<std::string> Book::keywords() const {
	std::set<std::string> keywords;
	std::set<std::string> nameset = parseStringToWords(name_);
	std::set<std::string>::iterator it;
	for(it = nameset.begin(); it!=nameset.end(); ++it){
		keywords.insert(*it);
	}
	keywords.insert(ISBN_);
	std::set<std::string> authorset = parseStringToWords(author_);
	std::set<std::string>::iterator it2;
	for(it2 = authorset.begin() ; it2 != authorset.end(); ++it2){
		keywords.insert(*it2);
	}
	return keywords;
}

std::string Book::displayString() const{
	stringstream ssconverter;
	//cout << getQty() << endl;
	ssconverter << price_ <<" "<< getQty();
	std::string price_string, qty_string;
	ssconverter >> price_string >> qty_string;
	std::string productinfo = name_+"\n"+"Author: " + author_ + " ISBN: " + ISBN_ +"\n"+price_string+ " "+qty_string+ " left.";
	return productinfo;
}

void Book::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << getQty() << "\n" << ISBN_ <<"\n" << author_<< endl;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
	
}
