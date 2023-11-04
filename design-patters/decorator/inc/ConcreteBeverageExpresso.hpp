#ifndef CONCRETE_BEVERAGE_EXPRESSO_H
#define CONCRETE_BEVERAGE_EXPRESSO_H

#include "AbstractBeverage.hpp"

class ConcreteBeverageExpresso : public AbstractBeverage {

    public:
        ConcreteBeverageExpresso() {
            description = "Expresso ";
        }
        double cost () {
            return 1.99;
        }

};

#endif /* CONCRETE_BEVERAGE_EXPRESSO_H */
