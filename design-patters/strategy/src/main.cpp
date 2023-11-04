#include <iostream>
//#include "mylib.h"
#include "AbstractDuck.hpp"
#include "MallardDuckConcrete.hpp"
#include "RubberDuckConcrete.hpp"

int main() {

    Duck *duck = new MallardDuckConcrete();
    duck->performFly();
    duck->performQuack();

    delete duck;
    duck = new RubberDuckConcrete();
    duck->performFly();

    
    return 0;
}
