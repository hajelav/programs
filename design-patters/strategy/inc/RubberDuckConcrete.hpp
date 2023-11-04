#ifndef RUBBER_DUCK_CONCRETE_H
#define RUBBER_DUCK_CONCRETE_H

#include "AbstractDuck.hpp"
#include "NoFlyConcrete.hpp"
#include <iostream>
using namespace std;


class RubberDuckConcrete : public Duck  {

    public:
        RubberDuckConcrete() {
            display();
            flyBehavior = new NoFlyConcrete();

        }

        void display() {
            cout << "I am a rubber duck" << endl;
        }

}; 


#endif /* RUBBER_DUCK_CONCRETE_H */
