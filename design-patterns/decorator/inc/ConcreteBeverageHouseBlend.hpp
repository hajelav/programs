#ifndef CONCRETE_BEVERAGE_HOUSEBLEND_H
#define CONCRETE_BEVERAGE_HOUSEBLEND_H

#include "AbstractBeverage.hpp"

class ConcreteBeverageHouseBlend : public AbstractBeverage {

    public:
        ConcreteBeverageHouseBlend() {
            description = "House Blend ";
        }
        double cost () {
            return 0.89;
        }

};

#endif /* CONCRETE_BEVERAGE_HOUSEBLEND_H */
