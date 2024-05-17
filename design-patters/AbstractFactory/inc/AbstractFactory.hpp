
// Abstract Factory
#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <iostream>
#include <memory>

#include "AbstractButton.hpp"

class AbstractFactory {
public:
    virtual std::shared_ptr<Button> createButton() = 0;
};

#endif // ABSTRACT_FACTORY_H
