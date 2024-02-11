#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore() {};

MyDataStore::~MyDataStore() {
  for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
    delete *it;
  }
  for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    delete it->second;
  }
};

void MyDataStore::addProduct(Product* p) {
  products_.insert(p);

  set<string> keywords = p->keywords();
  for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
    if (index_.find(*it) == index_.end()) {
      set<Product*> newSet;
      newSet.insert(p);
      index_.insert(make_pair(*it, newSet));
    }
    else {
      index_[*it].insert(p);
    }
  }
}
void MyDataStore::addUser(User* u) {
  users_[u->getName()] = u;
}
void MyDataStore::addToCart(string username, Product* product) {
  if (users_.find(username) == users_.end()) {
    cout << "Invalid request" << endl;
    return;
  }
  if (carts_.find(username) == carts_.end()) {
    vector<Product*> newCart;
    newCart.push_back(product);
    carts_.insert(make_pair(username,newCart));
  }
  else {
    carts_[username].push_back(product);
  }
}

void MyDataStore::viewCart(string username) {
  if (users_.find(username) == users_.end()) {
    cout << "Invalid username" << endl;
    return;
  }
  for (unsigned int i = 0; i < carts_[username].size(); ++i) {
    cout << "Item " << i+1 << endl;
    cout << (carts_[username][i])->displayString() << endl;
    cout << endl;
  }
  cout << endl;
}

void MyDataStore::buyCart(string username) {
  if (users_.find(username) == users_.end()) {
    cout << "Invalid username" << endl;
    return;
  }
  for (unsigned int i = 0; i < carts_[username].size(); ++i) {
    User* currUser = users_[username];
    Product* currProd = carts_[username][i];
    if (currProd->getQty() && currUser->getBalance() > currProd->getPrice()) {
      currProd->subtractQty(1);
      currUser->deductAmount(currProd->getPrice());
      carts_[username].erase(carts_[username].begin()+i);
      i--;
    }
  }
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
  vector<Product*> retVec;
  if (type == 0) {
    set<Product*> inter = products_;
    
    for (unsigned int i = 0; i < terms.size(); ++i) {
      inter = setIntersection(inter, index_[terms[i]]);
    }
    for (set<Product*>::iterator it = inter.begin(); it != inter.end(); ++it) {
      retVec.push_back(*it);
    }
    return retVec;
  }

  set<Product*> uni;

  for (unsigned int i = 0; i < terms.size(); ++i) {
    uni = setUnion(uni, index_[terms[i]]);
  }
  for (set<Product*>::iterator it = uni.begin(); it != uni.end(); ++it) {
      retVec.push_back(*it);
  }
  return retVec;
}

void MyDataStore::dump(ostream& ofile) {
  ofile << "<products>" << endl;
  for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
    (*it)->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    it->second->dump(ofile);
  }
  ofile << "</users>" << endl;
}