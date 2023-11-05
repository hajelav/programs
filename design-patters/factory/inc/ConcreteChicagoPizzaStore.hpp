#ifndef CONCRETE_CHICAGO_PIZZA_STORE_H
#define CONCRETE_CHICAGO_PIZZA_STORE_H

#include "PizzaStoreFactory.hpp"
#include "AbstractPizza.hpp"
#include "ConcreteChicagoStyleCheesePizza.hpp"
#include "ConcreteChicagoStyleVeggiePizza.hpp"



class ConcreteChicagoPizzaStore : public PizzastoreFactory {

       public:
        AbstractPizza* createPizza(string item) {
            if(item == "cheese") {
                pizza = new ConcreteChicagoStyleCheesePizza();

            } else if(item == "veggie") {
                pizza = new ConcreteChicagoStyleVeggiePizza();

            } else {
                return nullptr;
            }
            return pizza;

        }
       

};

#endif /* CONCRETE_CHICAGO_PIZZA_STORE_H */
