
#include <string>
#include <set>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "mydatastore.h"
#include "util.h"
#include "user.h"

using namespace std;

MyDataStore::MyDataStore(){

}
MyDataStore::~MyDataStore() {
	std::set<Product*>::iterator it;
	for (it = productset.begin(); it != productset.end(); ++it){
		delete *it;
	}
	std::map<std::string, User*>::iterator it2;
	for (it2 = usermap.begin(); it2 != usermap.end(); ++it2){
	 	delete (it2)->second;
	}
	// std::map<std::string, std::set<Product*>>::iterator it3;
	// for (it3 = cartmap.begin(); it3 != cartmap.end(); ++it3){
	//  	std::set<Product*>::iterator it4;
	// 	 for (it4 = ((it3)->second).begin(); it4 != ((it3)->second).end(); ++it4)
	// 	 delete *it4;
	// }
 }

    /**
     * Adds a product to the data store
     */
void MyDataStore::addProduct(Product* p) {
	productset.insert(p);
}

    /**
     * Adds a user to the data store
     */
void MyDataStore::addUser(User* u) {
	std::vector<Product*> cart;
	usermap.insert(make_pair(u->getName(), u));
	cartmap.insert(make_pair(u->getName(), cart));
}

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	std::vector<Product*> hitstoreturn;
	if (type == 0){
		std::vector<std::string>::iterator term;
		std::set<Product*> hits;
		int numterms = 0;
		for(term = terms.begin(); term!= terms.end(); ++term){
			std::set<Product*> termhits;
			std::set<Product*>::iterator it;
			for(it = productset.begin() ; it != productset.end(); ++it){
				std::set<std::string> keywordsset = (*it)->keywords();
				std::set<std::string>::iterator it2;
				for(it2 = keywordsset.begin(); it2 != keywordsset.end(); ++it2){
					if(*it2 == *term){
						termhits.insert(*it);
					}		
				}
			}
			if(numterms == 0){
				hits = termhits;
			}else{
				hits = setIntersection(hits, termhits);
			}
			++numterms;
		}
		std::set<Product*>::iterator it;
		for(it = hits.begin(); it!=hits.end(); ++it){
			hitstoreturn.insert(hitstoreturn.begin(),*it);
		}
	}else{
		std::vector<std::string>::iterator term;
		std::set<Product*> hits;
		int numterms = 0;
		for(term = terms.begin(); term!= terms.end(); ++term){
			std::set<Product*> termhits;
			std::set<Product*>::iterator it;
			for(it = productset.begin() ; it != productset.end(); ++it){
				std::set<std::string> keywordsset = (*it)->keywords();
				std::set<std::string>::iterator it2;
				for(it2 = keywordsset.begin(); it2 != keywordsset.end(); ++it2){
					if(*it2 == *term){
						termhits.insert(*it);
					}		
				}
			}
			if(numterms == 0){
				hits = termhits;
			}else{
				hits = setUnion(hits, termhits);
			}
			++numterms;
		}
		std::set<Product*>::iterator it;
		for(it = hits.begin(); it!=hits.end(); ++it){
			hitstoreturn.insert(hitstoreturn.begin(),*it);
		}
	}
	lastsearch = hitstoreturn;
	return hitstoreturn;
}

    /**
     * Reproduce the database file from the current Products and User values
     */
void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" <<"\n";
	std::set<Product*>::iterator it;
	for(it = productset.begin() ; it != productset.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile << "</products>" <<"\n";
	ofile << "<users>" <<"\n";
	std::map<std::string, User*>::iterator it2;
	for(it2 = usermap.begin() ; it2 != usermap.end(); ++it2){
		(it2->second)->dump(ofile);
	}
	ofile << "</users>" <<"\n";
}

void MyDataStore::viewcart(std::string username){
	if (cartmap.find(username) == cartmap.end()){
	 	cout << "Invalid username";
	 }else{
		int itemnum = 0;
	 	std::vector<Product*> printcart;
		std::vector<Product*>::iterator it;
		for(it = ((cartmap.find(username))->second).begin(); it != ((cartmap.find(username))->second).end(); ++it){
			++itemnum;
			cout <<"Item: "<<itemnum <<endl;
		//	cout <<(*it)->getQty()<<endl;
			cout << (*it)->displayString() << endl;
		}
	}
}

void MyDataStore::addtocart(std::string username, int hittoadd){
	if (cartmap.find(username) == cartmap.end()){
		cout << "Invalid request";
	}else if(hittoadd > lastsearch.size()){
		cout << "Invalid request" <<endl;
	}
	else{
		((cartmap.find(username))->second).push_back(lastsearch[hittoadd-1]);
	}
	
}

void MyDataStore::buycart(std::string username){
	
	if (cartmap.find(username) == cartmap.end()){
		cout << "Invalid username";
	}else{
		Product* item;
		for(int i = ((cartmap.find(username))->second).size(); i >= 0; --i){
			if(i = ((cartmap.find(username))->second).size()){
				--i;
			}
			item = (((cartmap.find(username))->second)[i]);
			if((((cartmap.find(username))->second)[i])->getQty()>0){
				if((((usermap.find(username))->second)->getBalance())>=((((cartmap.find(username))->second)[i])->getPrice())){
					(((cartmap.find(username))->second)[i])->subtractQty(1);
					(((usermap.find(username))->second)->deductAmount((((cartmap.find(username))->second)[i])->getPrice()));
					((cartmap.find(username))->second).erase(((cartmap.find(username))->second).begin()+i);
				}
			}
			// cout <<item->displayString()<<endl;
			// cout <<item->getQty()<<endl;
		}
	}
	// cout <<"DATABSESEE" << endl;
	// std::set<Product*>::iterator it;
	// for (it = productset.begin(); it != productset.end(); ++it){
	// 	cout<<(*it)->displayString()<<endl;
	// }

	
}





