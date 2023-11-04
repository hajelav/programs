#ifndef CONCRETE_CONDIMENT_DECORATOR_MOCHA_H
#define CONCRETE_CONDIMENT_DECORATOR_MOCHA_H


#include "AbstractCondimentDecorator.hpp"
//Cost of Mocha = 0.20

class ConcreteConditmentMocha : public AbstractCondimentDecorator {

    public:
        ConcreteConditmentMocha(AbstractBeverage* beverage) {
            this->beverge = beverage;
        }

        string getDescription() {
            return beverge->getDescription() + " Mocha";
        }

        double cost() {
            return beverge->cost() + 0.20;
        }

};


#endif /* CONCRETE_CONDIMENT_DECORATOR_MOCHA_H */
