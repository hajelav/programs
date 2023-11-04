#ifndef ABSTRACT_BEVERAGE_H
#define ABSTRACT_BEVERAGE_H

#include <iostream>

using namespace std;

class AbstractBeverage {

    public:
        AbstractBeverage() {
            description = "unknown beverage";
        }

        virtual string getDescription() {
            return description;
        }
        //make the cost method abstract as it needs to be implemented by subclasses
        virtual double cost() = 0;


        string description;
};

#endif /* ABSTRACT_BEVERAGE_H */
