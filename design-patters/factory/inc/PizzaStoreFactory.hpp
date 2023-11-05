#ifndef PIZZA_STORE_FACTORY_H
#define PIZZA_STORE_FACTORY_H

#include <iostream>
#include "AbstractPizza.hpp"

using namespace std;

class PizzastoreFactory {

    public:

        virtual  AbstractPizza* createPizza(string item) = 0;
        
        virtual void orderPizza(string type) {

            AbstractPizza *pizza = createPizza(type);
            pizza = createPizza(type);
            pizza->prepare();
            pizza->bake();
            pizza->cut();
            pizza->box();
        }

        AbstractPizza* pizza;
};


#endif /* PIZZA_STORE_FACTORY_H */
