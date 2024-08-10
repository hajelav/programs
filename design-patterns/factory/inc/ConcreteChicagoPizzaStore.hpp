#ifndef CONCRETE_CHICAGO_PIZZA_STORE_H
#define CONCRETE_CHICAGO_PIZZA_STORE_H

#include "PizzaStoreFactory.hpp"
#include "AbstractPizza.hpp"
#include "ConcreteChicagoStyleCheesePizza.hpp"
#include "ConcreteChicagoStyleVeggiePizza.hpp"



class ConcreteChicagoPizzaStore : public PizzastoreFactory {

       public:
       ConcreteChicagoPizzaStore() {
           pizza = nullptr;
           cout << "ChicagoPizzaStore constructed" << endl;
       }
        shared_ptr<AbstractPizza> createPizza(string item) {
            if(item == "cheese") {
                pizza = make_shared<ConcreteChicagoStyleCheesePizza>();

            } else if(item == "veggie") {
                pizza = make_shared<ConcreteChicagoStyleVeggiePizza>();

            } else {
                return nullptr;
            }
            return pizza;

        }
       

};

#endif /* CONCRETE_CHICAGO_PIZZA_STORE_H */
