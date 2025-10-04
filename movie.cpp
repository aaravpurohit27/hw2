#include "movie.h"
#include "util.h"
#include <sstream>
#include <string>
#include <iostream>

Movie::Movie(const std::string& category, const std::string& name, double price, int qty, const std::string& genre, const std::string& rating):Product(category, name, price, qty)
{
  genre_ = genre;
  rating_ = rating;
}

std::set<std::string> Movie::keywords() const{
  std::set<std::string>kwords=parseStringToWords(convToLower(name_));
  std::set<std::string>gwords = parseStringToWords(convToLower(genre_));
  for(std::set<std::string>::iterator it = gwords.begin(); it!=gwords.end(); ++it){
    kwords.insert(*it);
  }
  kwords.insert(convToLower(rating_));
  return kwords;
}

std::string Movie::displayString() const{
  std::ostringstream os;
  os<<name_<<std::endl
    <<"Genre: "<<genre_ << " Rating: "<<rating_<<std::endl
    <<price_<<" "<<qty_<<" left";
  return os.str();
}

void Movie::dump(std::ostream& os) const{
  os<<category_<<std::endl<<name_<<std::endl<<price_<<std::endl<<qty_<<std::endl<<genre_<<std::endl<<rating_<<std::endl;
}