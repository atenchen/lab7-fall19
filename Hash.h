#ifndef HASH_H
#define HASH_H
#include "Node.h"
#include <iostream>
#include <string>

class Hash{
 private:
  Node* array;
  unsigned int a_size;
  unsigned int numItem;
 public:
  Hash(unsigned int size);
  ~Hash();
  bool isPrime(int num);
  int nearestPrime(int num);
  unsigned int hasher(std::string key);
  unsigned int hasher2(std::string key);
  bool insert(std::string key, double value);
  bool empty(){return numItem == 0;}
  unsigned int size(){return this->a_size;}
  Node * getTable(){return this->array;}
  bool remove(std::string key);
  double find(std::string key);
};
#endif
