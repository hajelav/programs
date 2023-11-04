#ifndef FLY_WITH_WINGS_H
#define FLY_WITH_WINGS_H

#include "AbstractFlyBehavior.hpp"
#include <iostream>

using namespace std;

class FlyWithWings : public AbstractFlyBehavior {

    void fly(void) {
        cout << "I can fly with wings" << endl;
    }
 };

#endif /* FLY_WITH_WINGS_H */
