#ifndef CONCRETE_NY_STYLE_CHEESE_PIZZA_H
#define CONCRETE_NY_STYLE_CHEESE_PIZZA_H

#include "AbstractPizza.hpp"

using namespace std;

class ConcreteNYStyleCheesePizza : public AbstractPizza {

    public:
        ConcreteNYStyleCheesePizza() {
            name = "NY style Sauce and cheese Pizza";
            dough = "Thin crust";
            sauce = "Marinara";
            toppings.push_back("grated raggiano cheese");
        }
               
};

#endif /* CONCRETE_NY_STYLE_CHEESE_PIZZA_H */
