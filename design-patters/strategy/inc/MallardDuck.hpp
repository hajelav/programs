#ifndef MALLARD_DUCK_H
#define MALLARD_DUCK_H

#include "AbstractDuck.hpp"
#include "FlyWithWings.hpp"
#include <iostream>
using namespace std;

class MallardDuck : public Duck {

    public:
        MallardDuck() {
            //here is where we connect the abstract flybehavior to the concrete subclass
            flyBehavior = new FlyWithWings();
        }
        void display(void) {
            cout << "I am a mallard duck" << endl;
        }

};


#endif /* MALLARD_DUCK_H */
