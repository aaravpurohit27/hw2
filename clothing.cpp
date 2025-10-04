#include "clothing.h"
#include "util.h"
#include <sstream>
#include <string>
#include <iostream>

Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty, const std::string& size, const std::string& brand):Product(category, name, price, qty)
{
  size_ = size;
  brand_ = brand;
}

std::set<std::string> Clothing::keywords() const{
  std::set<std::string>kwords= parseStringToWords(convToLower(name_));
  std::set<std::string>bwords = parseStringToWords(convToLower(brand_));
  for(std::set<std::string>::iterator it = bwords.begin(); it!=bwords.end(); ++it){
    kwords.insert(*it);
  }
  kwords.insert(convToLower(size_));
  return kwords;
}

std::string Clothing::displayString() const{
  std::ostringstream os;
  os<<name_<<std::endl
    <<"Size: "<<size_<<" Brand: "<<brand_<<std::endl
    <<price_<<" "<<qty_<<" left";
  return os.str();
}

void Clothing::dump(std::ostream& os) const{
  os<<category_<<std::endl<<name_<<std::endl<<price_<<std::endl<<qty_<<std::endl<<size_<<std::endl<<brand_<<std::endl;
}