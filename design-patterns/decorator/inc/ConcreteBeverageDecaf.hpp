#ifndef CONCRETE_BEVERAGE_DECAF_H
#define CONCRETE_BEVERAGE_DECAF_H

#include "AbstractBeverage.hpp"

class ConcreteBeverageDecaf : public AbstractBeverage {

    public:
        ConcreteBeverageDecaf() {
            description = "Decaf ";
        }
        double cost () {
            return 1.05;
        }

};

#endif /* CONCRETE_BEVERAGE_DECAF_H */
