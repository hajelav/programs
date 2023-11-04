#ifndef FLY_WITH_WINGS_CONCRETE_H
#define FLY_WITH_WFLY_WITH_WINGS_CONCRETE_HINGS_H

#include "AbstractFlyBehavior.hpp"
#include <iostream>

using namespace std;

class FlyWithWingsConcrete : public AbstractFlyBehavior {

    void fly(void) {
        cout << "I can fly with wings" << endl;
    }
 };

#endif /* FLY_WITH_WINGS_CONCRETE_H */
