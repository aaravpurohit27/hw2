#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <iostream>



MyDataStore::MyDataStore()
{}

//remember to implement later
MyDataStore::~MyDataStore()
{
  //clean product vector
  for(size_t i=0; i<products_.size(); i++){
    delete products_[i];
  }
  //clear user map
  for(std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    delete it->second; //second because use is second thing in the map
  }

}


void MyDataStore::addProduct(Product* p){
  products_.push_back(p);

  //keywords
  std::set<std::string> kwords = p->keywords();
  //iterating through a set, use lab example
  for(std::set<std::string>::iterator it=kwords.begin(); it != kwords.end(); ++it){
    std::string word = convToLower(*it);
    kdex_[word].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  std::string user = u->getName();
  users_[user] = u;
  //adding user u to user map

  //adding a cart to the user by checking if a cart for that user already exists
  //use example from lab
  if(cart_.find(user) == cart_.end()){
    cart_[user] = std::vector<Product*>();
  }

}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::vector<Product*> resulto;
  std::set<Product*> rset;
  if(terms.size() == 0){
    return resulto;
  }
  std::string start = convToLower(terms[0]);
  if(kdex_.find(start) != kdex_.end()){
    rset = kdex_[start];
  }

  //And search is type 0 intersection, or is type 1 union
  if(type == 0){
    for(size_t i=1; i<terms.size(); i++){
      std::string k=convToLower(terms[i]);
      if(kdex_.find(k) != kdex_.end()){
        rset = setIntersection(rset, kdex_[k]);
      }
    }
  }
  else{ //type 1
    for(size_t i=1; i<terms.size(); i++){
      std::string k = convToLower(terms[i]);
      if(kdex_.find(k) != kdex_.end()){
        //needs to be set lwk
        rset = setUnion(rset, kdex_[k]);
      }
    }
  }
  for(std::set<Product*>::iterator it=rset.begin(); it!=rset.end(); ++it){
    resulto.push_back(*it);
  }

  return resulto;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile<<"<products>" <<std::endl;
  for(size_t i=0; i<products_.size(); i++){
    //use the dump function from product.h
    products_[i]->dump(ofile);
  }
  ofile << "</products>" <<std::endl;

  ofile<<"<users>"<<std::endl;
  //users is a map, needs to iterate like a map
  for(std::map<std::string, User*>::iterator it=users_.begin(); it != users_.end(); ++it){
    it->second->dump(ofile);
  }
  ofile << "</users>" <<std::endl;
}



void MyDataStore::addToCart(const std::string& username, Product* p){
  std::string user = username;
  if(users_.find(user) != users_.end()){
    cart_[user].push_back(p);
  }
  else{
    std::cout<<"Invalid username"<<std::endl;
  }
}

void MyDataStore::viewCart(const std::string& username)const{
  std::string user = username;
  if(cart_.find(username) == cart_.end()){
    std::cout<<"invalid username"<<std::endl;
    return; //no user so no cartation
  }
  const std::vector<Product*>& items = cart_.find(username)->second;
  for(size_t i=0; i<items.size(); i++){
    std::cout<<"Item "<<i+1<<std::endl;
    std::cout<<items[i]->displayString()<<std::endl;
  }
}

//do buy cart tomorrow during class or sumthign
//oh and do dump once figure out

void MyDataStore::buyCart(const std::string& username){
  std::string user = username;
  //check if user and cart exists
  if(cart_.find(user) == cart_.end()){
    std::cout<<"Invalid username"<<std::endl;
    return;
  }
  //make a reference to the cart of our user?
  std::vector<Product*>& u_cart = cart_[user];
  //vector for stuff user cant afford or doesn't have enough quantity
  std::vector<Product*> cant_buy;
  for(size_t i=0; i<u_cart.size(); i++){
    Product* prod = u_cart[i];
    //iterate throught the cart to check if product qty is not 0 and if user can afford
    if(prod->getQty() > 0) {
      if(prod->getPrice() <= users_[user]->getBalance()){
        //good to go to buy the cart
        //reduce user's money
        
        users_[user]->deductAmount(prod->getPrice());
        //take away 1 quantity
        prod->subtractQty(1);
      }
      else{
        cant_buy.push_back(prod);
      }
    }
    else{
      cant_buy.push_back(prod);
    }
  }
  //replace cart with everything that couldn't be bought
  u_cart.clear();
  for(size_t i=0; i<cant_buy.size(); i++){
    u_cart.push_back(cant_buy[i]);
  }

}