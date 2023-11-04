#ifndef ABSTRACT_DUCK_H
#define ABSTRACT_DUCK_H

#include "AbstractFlyBehavior.hpp"

class Duck {

    public:
        void swim() {}
        virtual void display() = 0;
        Duck() {}
        ~Duck() {}
        void performFly() {
            flyBehavior->fly();
        }
    
        AbstractFlyBehavior* flyBehavior;
        

};

#endif /* ABSTRACT_DUCK_H */
