#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

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
