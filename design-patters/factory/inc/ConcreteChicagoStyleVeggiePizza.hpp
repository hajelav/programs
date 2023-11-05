#ifndef CONCRETE_CHICAGO_STYLE_VEGGIE_PIZZA_H
#define CONCRETE_CHICAGO_STYLE_VEGGIE_PIZZA_H

#include "AbstractPizza.hpp"

using namespace std;

class ConcreteChicagoStyleVeggiePizza : public AbstractPizza {

    public:
        ConcreteChicagoStyleVeggiePizza() {
            name = "Chicago style deep dish veggie pizza";
            dough = "Extra thick crust";
            sauce = "Plum tomato sauce";
            toppings.push_back("grated raggiano cheese");
        }
        //overriding the function from the base class
        void cut() override {
            cout << "Cutting the pizza into square slices" << endl;
        }
        
};

#endif /* CONCRETE_CHICAGO_STYLE_VEGGIE_PIZZA_H */
