#ifndef CONCRETE_CONDIMENT_DECORATOR_MILK_H
#define CONCRETE_CONDIMENT_DECORATOR_MILK_H


#include "AbstractCondimentDecorator.hpp"
//Cost of Milk = 0.10

class ConcreteConditmentMilk : public AbstractCondimentDecorator {

    public:
        ConcreteConditmentMilk(AbstractBeverage* beverage) {
            this->beverge = beverage;
        }

        string getDescription() {
            return beverge->getDescription() + " Milk";
        }

        double cost() {
            return beverge->cost() + 0.10;
        }

};


#endif /* CONCRETE_CONDIMENT_DECORATOR_MILK_H */
