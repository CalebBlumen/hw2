#include "clothing.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <sstream>


using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand) :
    Product(category, name, price, qty), 
    size_(size), 
    brand_(brand) {}

set<string> Clothing::keywords() const {
    set<string> words = parseStringToWords(name_);
    set<string> sizeWords = parseStringToWords(size_);
    set<string> brandWords = parseStringToWords(brand_);
    for (set<string>::iterator it = sizeWords.begin(); it != sizeWords.end(); ++it) {
      words.insert(*it);
    }
    for (set<string>::iterator it = brandWords.begin(); it != brandWords.end(); ++it) {
      words.insert(*it);
    }
    return words;
}

string Clothing::displayString() const {
  stringstream ss;
  ss << fixed << setprecision(2) << price_;
  string priceString;
  ss >> priceString;
  string outstr = name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + priceString + " " + to_string(qty_) + " left.";
  return outstr;
} 

void Clothing::dump(ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

string Clothing::getSize() const {
  return size_;
}

string Clothing::getBrand() const {
  return brand_;
}

