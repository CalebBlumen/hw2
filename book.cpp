#include "book.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <sstream>


using namespace std;

Book::Book(const string category, const string name, double price, int qty, string isbn, string author) :
    Product(category, name, price, qty), 
    isbn_(isbn), 
    author_(author) {}

set<string> Book::keywords() const {
    set<string> words = parseStringToWords(name_);
    set<string> authorWords = parseStringToWords(author_);

    for (set<string>::iterator it = authorWords.begin(); it != authorWords.end(); ++it) {
      words.insert(*it);
    }

    words.insert(isbn_);
    return words;
}

string Book::displayString() const {
  stringstream ss;
  ss << fixed << setprecision(2) << price_;
  string priceString;
  ss >> priceString;
  string outstr = name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + priceString + " " + to_string(qty_) + " left.";
  return outstr;
} 

void Book::dump(ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

string Book::getIsbn() const {
  return isbn_;
}

string Book::getAuthor() const {
  return author_;
}


