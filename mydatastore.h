#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"

class MyDataStore : public DataStore {
  public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::string,Product*);
    void viewCart(std::string);
    void buyCart(std::string);
  private: 
    std::map<std::string, User*> users_;
    std::set<Product*> products_;
    std::map<std::string, std::set<Product*>> index_;
    std::map<std::string, std::vector<Product*>> carts_;
    
};
#endif