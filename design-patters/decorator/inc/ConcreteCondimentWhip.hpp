#ifndef CONCRETE_CONDIMENT_DECORATOR_WHIP_H
#define CONCRETE_CONDIMENT_DECORATOR_WHIP_H


#include "AbstractCondimentDecorator.hpp"
//Cost of Whip = 0.10

class ConcreteConditmentWhip : public AbstractCondimentDecorator {

    public:
        ConcreteConditmentWhip(AbstractBeverage* beverage) {
            this->beverge = beverage;
        }

        string getDescription() {
            return beverge->getDescription() + " Milk";
        }

        double cost() {
            return beverge->cost() + 0.10;
        }

};


#endif /* CONCRETE_CONDIMENT_DECORATOR_WHIP_H */
