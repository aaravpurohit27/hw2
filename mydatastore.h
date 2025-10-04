#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include "util.h"
#include "user.h"
#include "datastore.h"
#include "product.h"

class MyDataStore : public DataStore{
public:
  MyDataStore();
  ~MyDataStore();

  void addProduct(Product* p);
  void addUser(User* u);

  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  void dump(std::ostream& ofile);

  void addToCart(const std::string& username, Product* p);
  void viewCart(const std::string& username) const;
  void buyCart(const std::string& username);

private:
  //vector for products because no need for keys to another element
  std::vector<Product*> products_;
  //map for users for name lookup?? probably
  std::map<std::string, User*> users_;
  //map for keywords to match keywords to products OH cuz match it to the products vectoor lwk
  std::map<std::string, std::set<Product*>> kdex_;
  //map for cart since every user has a cart, also works well with the 3 cart functions needed
  std::map<std::string, std::vector<Product*>> cart_;
};
#endif