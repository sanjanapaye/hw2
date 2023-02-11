#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
// #include "product.h"
// #include "db_parser.h"
// #include "product_parser.h"
// #include "util.h"
// #include "book.h"
// #include "mydatastore.h"
using namespace std;
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
                keywords.insert(word1);
            }
            ss2 >> word2;
            if(word2.size()>=2){
                keywords.insert(word2);
            }
        }else{
            keywords.insert(word);
        }
    }
    return keywords;
}

class Product {
public:
    Product(const std::string category, const std::string name, double price, int qty);
    virtual ~Product();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    virtual std::set<std::string> keywords() const = 0;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    virtual std::string displayString() const = 0;

    /**
     * Outputs the product info in the database format
     */
    virtual void dump(std::ostream& os) const;

    /**
     * Accessors and mutators
     */
    double getPrice() const;
    std::string getName() const;
    int getQty() const;
    void subtractQty(int num);

protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;

};
Product::Product(const std::string category, const std::string name, double price, int qty) :
    name_(name),
    price_(price),
    qty_(qty),
    category_(category)
{

}

Product::~Product()
{

}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}

class Book : public Product {
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author);
     
    ~Book();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
		std::set<std::string> keywords() const override;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
  	std::string displayString() const override;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;


protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;
		std::string ISBN_;
		std::string author_;

};
Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author): Product(category, name, price, qty)
{
    name_= name;
    category_ = category;
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
	ssconverter << price_ <<" "<< qty_;
	std::string price_string, qty_string;
	ssconverter >> price_string >> qty_string;
	std::string productinfo = name_+"\n"+"Author: " + author_ + " ISBN: " + ISBN_ +"\n"+price_string+ " "+qty_string+ " left";
	return productinfo;
}

void Book::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << to_string(price_) << "\n" << to_string(qty_) << "\n" << ISBN_ <<"\n" << author_<< endl;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
	
}

int main(int argc, char* argv[])
{
	//testing parser
	// std::string rawwords = "Men's small j. shirts.";
	// std::set<std::string> keywordstest = parseStringToWords(rawwords);
	// std::set<std::string>::iterator it;
	// for(it = keywordstest.begin(); it!=keywordstest.end(); ++it){
	// 	cout << *it << endl;
	// }

	//testing intersction/union
	// std::set<std::string> set1, set2;
	// set1.insert("hi");
	// set1.insert("hello");
	// set2.insert("hello");
	// set2.insert("goodbye");
	// std::set<std::string>	together = setUnion(set1, set2);
	// std::set<std::string>::iterator it;
	// for(it = together.begin(); it!=together.end(); ++it){
	// 	cout << *it << endl;
	// }

	//testing product classes

    // Book* newbook = new Book("book", "Of Mice and men", 20.0, 2, "6066310000", "John Steinbeck");
    // std::string info = newbook->displayString();
	// // std::set<std::string>::iterator it;
	// // for(it = keywords1.begin(); it!=keywords1.end(); ++it){
	// // 	cout << *it << endl;
	// // }
    // cout << info <<endl;

    std::ofstream ifile("databaseout.txt");
	ifile << "hey" << std::endl;
	ifile.close();

    return 0;
}