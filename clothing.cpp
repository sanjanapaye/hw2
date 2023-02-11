#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
  Product(category, name, price, qty)
{
	category_ = category;
	name_ = name;
	price_ = price;
	qty_ = qty;
	size_=size;
	brand_=brand;
}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const {
	std::set<std::string> keywords;
	typename std::set<std::string> nameset = parseStringToWords(name_);
	typename std::set<std::string>::iterator it;
	for(it = nameset.begin() ; it != nameset.end(); ++it){
		keywords.insert(*it);
	}
	typename std::set<std::string> brandset = parseStringToWords(brand_);
	typename std::set<std::string>::iterator it2;
	for(it2 = brandset.begin() ; it2 != brandset.end(); ++it2){
		keywords.insert(*it2);
	}
	return keywords;
}

std::string Clothing::displayString() const {
	stringstream ssconverter;
	ssconverter << price_ <<" "<< getQty();
	std::string price_string, qty_string;
	ssconverter >> price_string >> qty_string;
	std::string productinfo = name_+"\n"+"Size: " + size_ + " Brand: " + brand_ +"\n"+price_string+" "+qty_string+ " left";
	return productinfo;
}

void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << getQty()<< "\n" << size_ <<"\n" << brand_<< endl;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
	
}