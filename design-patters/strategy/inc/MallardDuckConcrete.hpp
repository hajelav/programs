#ifndef MALLARD_DUCK_CONCRETE_H
#define MALLARD_DUCK_CONCRETE_H

#include "AbstractDuck.hpp"
#include "FlyWithWingsConcrete.hpp"
#include "QuackConcrete.hpp"
#include <iostream>
using namespace std;

class MallardDuckConcrete : public Duck {

    public:
        MallardDuckConcrete() {

            display();
            //here is where we connect the abstract flybehavior to the concrete subclass
            flyBehavior = new FlyWithWingsConcrete();
            quackBehaviour = new QuackConcrete();
        }
        void display(void) {
            cout << "I am a mallard duck" << endl;
        }

};


#endif /* MALLARD_DUCK_CONCRETE_H */
