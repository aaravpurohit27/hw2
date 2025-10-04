#include "book.h"
#include "util.h"
#include <sstream>
#include <string>
#include <iostream>

Book::Book(const std::string& category, const std::string& name, double price, int qty, const std::string& author, const std::string& isbn):Product(category, name, price, qty)
{
  author_ = author;
  isbn_ = isbn;
}

std::set<std::string> Book::keywords() const{
  std::set<std::string> kwords = parseStringToWords(name_);
  std::set<std::string> awords = parseStringToWords(author_);
  for(std::set<std::string>::iterator it = awords.begin(); it!=awords.end(); ++it){
    kwords.insert(*it);
  }
  kwords.insert(convToLower(isbn_));
  return kwords;
}

std::string Book::displayString() const{
  std::ostringstream os;
  os<<name_<<std::endl
    <<"Author: "<<author_<<" ISBN: "<<isbn_<<std::endl
    <<price_<<" "<<qty_<<" left";
  return os.str();
}

void Book::dump(std::ostream& os) const{
  os<<category_<<std::endl
  <<name_<<std::endl
  <<price_<<std::endl
  <<qty_<<std::endl
  <<isbn_<<std::endl
  <<author_<<std::endl;
}