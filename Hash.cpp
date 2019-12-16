#include "Hash.h"
#include <iostream>
#include <string>

Hash::Hash(unsigned int size){
  array = new Node[size];
  this->a_size = size;
  numItem = 0;
}

Hash::~Hash(){
  delete[] array;
}
bool Hash::isPrime(int n) {
    for(int i = 2; i <= n/2; i++){
        if(n%i == 0) return false;
    }
    return true;
}

int Hash::nearestPrime(int num){
  if(num <= 3){
    return 3;
  }
  int prime = num - 1;
  while(!isPrime(prime)){
    prime--;
  }
  return prime;
}

unsigned int Hash::hasher(std::string key){
  unsigned int ascii = 0;
  for(int i = 0; key[i] != '\0'; i++){
    ascii += (unsigned int)key[i];
  }
  return ascii % a_size;
}

unsigned int Hash::hasher2(std::string key){
  unsigned int prime = (unsigned int)nearestPrime(a_size);
  unsigned int ascii = 0;
  for(int i = 0; key[i] != '\0'; i++){
    ascii += (unsigned int)key[i];
  }
  unsigned int index = prime - (ascii % prime);
  return index;
}
bool Hash::insert(std::string key, double value){
  if(numItem >= a_size){
    return false;
  }
  unsigned int index1 = hasher(key);
  if(array[index1].key.compare("")==0){
    array[index1].key = key;
    array[index1].value = value;
    numItem++;
    return true;
  }
  unsigned int index2 = hasher2(key);
  if(array[index2].key.compare("")==0){
    array[index2].key = key;
    array[index2].value = value;
    numItem++;
    return true;
  }
  unsigned int index3 =  index1 + index2;
  unsigned int increment = 1;
  while(increment < a_size){
    if(array[(index3 + increment) % a_size].key.compare("")==0){
      array[(index3 + increment) % a_size].key = key;
      array[(index3 + increment) % a_size].value = value;
      numItem++;
      return true;
    }
    increment++;
  }
  return false;
}

double Hash::find(std::string key){
  unsigned int index1 = hasher(key);
  if(array[index1].key.compare(key) == 0){
    return array[index1].value;
  }
  unsigned int index2 = hasher2(key);
  if(array[index2].key.compare(key) == 0){
    return array[index2].value;
  }
  unsigned int index3 = index1 + index2;
  unsigned int increment = 1;
  while(increment < a_size){
    if(array[(index3 + increment) % a_size].key.compare(key) == 0){
      return array[(index3 + increment) % a_size].value;
    }
    increment++;
  }
  return -1.0;
}

bool Hash::remove(std::string key){
  unsigned int index1 = hasher(key);
  if(array[index1].key.compare(key) == 0){
    array[index1].value = -1.0;
    array[index1].key = "";
    numItem--;
    return true;
  }
  unsigned int index2 = hasher2(key);
  if(array[index2].key.compare(key) == 0){
    array[index2].value = -1.0;
    array[index2].key =	"";
    numItem--;
    return true;
  }
  unsigned int index3 = index1 + index2;
  unsigned int increment = 0;
  while(increment < a_size){
    if(array[(index3 + increment) % a_size].key.compare(key) == 0){
      array[(index3 + increment) % a_size].value = -1.0;
      array[(index3 + increment) % a_size].key = "";
      numItem--;
      return true;
    }
    increment ++;
  }
  return false;
}
