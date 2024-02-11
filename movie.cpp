#include "movie.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <set>


using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating) :
    Product(category, name, price, qty), 
    genre_(genre), 
    rating_(rating) {}

set<string> Movie::keywords() const {
    set<string> words = parseStringToWords(name_);
    set<string> ratingWords = parseStringToWords(rating_);

    for (set<string>::iterator it = ratingWords.begin(); it != ratingWords.end(); ++it) {
      words.insert(*it);
    }
    words.insert(convToLower(genre_));
    return words;
}

string Movie::displayString() const {
  stringstream ss;
  ss << fixed << setprecision(2) << price_;
  string priceString;
  ss >> priceString;
  string outstr = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + priceString + " " + to_string(qty_) + " left.";
  return outstr;
} 

void Movie::dump(ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

string Movie::getGenre() const {
  return genre_;
}

string Movie::getRating() const {
  return rating_;
}

