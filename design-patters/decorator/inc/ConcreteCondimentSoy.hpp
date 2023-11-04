#ifndef CONCRETE_CONDIMENT_DECORATOR_SOY_H
#define CONCRETE_CONDIMENT_DECORATOR_SOY_H


#include "AbstractCondimentDecorator.hpp"
//Cost of Soy = 0.15

class ConcreteConditmentSoy : public AbstractCondimentDecorator {

    public:
        ConcreteConditmentSoy(AbstractBeverage* beverage) {
            this->beverge = beverage;
        }

        string getDescription() {
            return beverge->getDescription() + " Soy";
        }

        double cost() {
            return beverge->cost() + 0.15;
        }

};


#endif /* CONCRETE_CONDIMENT_DECORATOR_MILK_H */
