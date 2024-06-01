#ifndef QUACK_CONCRETE_H
#define QUACK_CONCRETE_H

#include "AbstractQuackBehavior.hpp"
#include <iostream>

using namespace std;

class QuackConcrete : public AbstractQuackBehaviour {

  void quack() {
    cout << "I quack" << endl;
  }  
};
 
#endif /* QUACK_CONCRETE_H */
