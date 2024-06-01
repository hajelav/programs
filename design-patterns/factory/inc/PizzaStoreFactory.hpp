#ifndef PIZZA_STORE_FACTORY_H
#define PIZZA_STORE_FACTORY_H

#include <iostream>
#include "AbstractPizza.hpp"
#include <memory>

using namespace std;

class PizzastoreFactory {

    public:

        virtual  shared_ptr<AbstractPizza> createPizza(string item) = 0;
        
        virtual void orderPizza(string type) {

            shared_ptr<AbstractPizza> pizza = createPizza(type);
            //pizza = createPizza(type);
            pizza->prepare();
            pizza->bake();
            pizza->cut();
            pizza->box();
        }

        shared_ptr<AbstractPizza> pizza;
};


#endif /* PIZZA_STORE_FACTORY_H */
