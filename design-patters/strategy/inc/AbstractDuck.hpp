#ifndef ABSTRACT_DUCK_H
#define ABSTRACT_DUCK_H

#include "AbstractFlyBehavior.hpp"
#include "AbstractQuackBehavior.hpp"

class Duck {

    public:
        void swim() {}
        virtual void display() = 0;
        Duck() {}
        ~Duck() {}
        void performFly() {
            flyBehavior->fly();
        }
        void performQuack() {
            quackBehaviour->quack();
        }
    
        AbstractFlyBehavior* flyBehavior;
        AbstractQuackBehaviour* quackBehaviour; 

        

};

#endif /* ABSTRACT_DUCK_H */
