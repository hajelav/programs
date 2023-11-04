#include <iostream>
//#include "mylib.h"
#include "AbstractDuck.hpp"
#include "MallardDuck.hpp"

int main() {

    Duck *duck = new MallardDuck();
    duck->performFly();
    
    return 0;
}
