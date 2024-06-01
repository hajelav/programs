#ifndef NO_FLY_CONCRETE_H
#define NO_FLY_CONCRETE_H

#include "AbstractFlyBehavior.hpp"
#include <iostream>

using namespace std;

class NoFlyConcrete : public AbstractFlyBehavior {
    void fly() {
        cout << "I cannot fly" << endl;
    }
};

#endif /* NO_FLY_CONCRETE_H */
