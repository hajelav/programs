#ifndef CONCRETE_NY_PIZZA_STORE_H
#define CONCRETE_NY_PIZZA_STORE_H

#include "PizzaStoreFactory.hpp"
#include "AbstractPizza.hpp"
#include "ConcreteNYStyleCheesePizza.hpp"
#include "ConcreteNYStyleVeggiePizza.hpp"

using namespace std;

class ConcreteNYPizzaStore : public PizzastoreFactory {

    public:
        shared_ptr<AbstractPizza> createPizza(string item) {
            if(item == "cheese") {
                pizza = make_shared<ConcreteNYStyleCheesePizza>();

            } else if(item == "veggie") {
                pizza = make_shared<ConcreteNYStyleVeggiePizza>();

            } else {
                return nullptr;
            }
            return pizza;
        }
};

#endif /* CONCRETE_NY_PIZZA_STORE_H */
