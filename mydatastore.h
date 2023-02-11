#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include "datastore.h"


class MyDataStore : public DataStore {
public:
    //constructor
		MyDataStore();

		//destructor
		~MyDataStore();
    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

		void viewcart(std::string username);

    void addtocart(std::string username, int hittoadd);
    void buycart(std::string username);
		std::set<Product*> productset;
    std::map<std::string, User*> usermap;
		std::map<std::string, std::vector<Product*>> cartmap;
    std::vector<Product*> lastsearch;


};

#endif
