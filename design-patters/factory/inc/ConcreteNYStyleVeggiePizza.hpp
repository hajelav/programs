#ifndef CONCRETE_NY_STYLE_VEGGIE_PIZZA_H
#define CONCRETE_NY_STYLE_VEGGIE_PIZZA_H

#include "AbstractPizza.hpp"

using namespace std;

class ConcreteNYStyleVeggiePizza : public AbstractPizza {

    public:
        ConcreteNYStyleVeggiePizza() {
            name = "NY style Sauce and veggie Pizza";
            dough = "Thin crust dough";
            sauce = "Marinara sauce";
            toppings.push_back("Onions, pepper, mushrooms");
        }
        
};

#endif /* CONCRETE_NY_STYLE_VEGGIE_PIZZA_H */
