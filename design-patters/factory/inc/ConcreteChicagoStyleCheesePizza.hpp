#ifndef CONCRETE_CHICAGO_STYLE_CHEESE_PIZZA_H
#define CONCRETE_CHICAGO_STYLE_CHEESE_PIZZA_H

#include "AbstractPizza.hpp"

using namespace std;

class ConcreteChicagoStyleCheesePizza : public AbstractPizza {

    public:
        ConcreteChicagoStyleCheesePizza() {
            name = "Chicago style deep dish cheese pizza";
            dough = "Extra thick crust";
            sauce = "Plum tomato sauce";
            toppings.push_back("grated raggiano cheese");
        }
        //overriding the function from the base class
        void cut() override {
            cout << "Cutting the chiago style cheese pizza into square slices" << endl;
        }
        
};

#endif /* CONCRETE_NY_STYLE_CHEESE_PIZZA_H */
