#ifndef CONCRETE_BEVERAGE_DARKROAST_H
#define CONCRETE_BEVERAGE_DARKROAST_H

#include "AbstractBeverage.hpp"

class ConcreteBeverageDarkRoast : public AbstractBeverage {

    public:
        ConcreteBeverageDarkRoast() {
            description = "Dark Roast ";
        }
        double cost () {
            return 0.99;        
        }

};

#endif /* CONCRETE_BEVERAGE_DARKROAST_H */
