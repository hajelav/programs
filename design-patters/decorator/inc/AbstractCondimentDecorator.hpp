#ifndef ABSTRACT_CONDIMENT_DECORATOR_H
#define ABSTRACT_CONDIMENT_DECORATOR_H

#include "AbstractBeverage.hpp"

class AbstractCondimentDecorator : public AbstractBeverage{

    public:

        virtual string getDescription() = 0;
        AbstractBeverage *beverge;
};

#endif /* ABSTRACT_CONDIMENT_DECORATOR_H */
