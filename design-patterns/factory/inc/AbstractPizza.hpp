#ifndef ABSTRACT_PIZZA_H
#define ABSTRACT_PIZZA_H


#include <iostream>
#include <vector>

using namespace std;

class AbstractPizza {

    public:

        /**
         * A method to prepare the pizza by tossing dough, adding sauce, and toppings.
         *
         * @return void
         *
         */
        void prepare() {
            cout << "Preparing " << name << endl;
            cout << "Tossing " << dough << " dough..." << endl;
            cout << "Adding " << sauce  << " sauce..." << endl;
            cout << "Adding toppings : ";
            for(auto &a : toppings)
                cout << a << " ";
            cout << endl;
        }

        virtual void bake() {
            cout << "Bake for 25 mins at 350 C" << endl;
        }
        virtual void cut() {
            cout << "Cutting the pizza into diagonal slices" << endl;
        }
        virtual void box() {
            cout << "Place pizza in official PizzaStore box" << endl;
        }
        
        string getName() {
            return name;
        }

        string name;
        string dough;
        string sauce;
        vector<string> toppings;






};

#endif /* ABSTRACT_PIZZA_H */
