#ifndef CONCRETE_CLASS_B_H
#define CONCRETE_CLASS_B_H

#include "AbstractTemplateClass.hpp"
#include  <iostream>

using namespace std;

class ConcreteClassB : public AbstractTemplateClass {

    void step2() override {
        cout << "ConcreteClassB : step2" << endl;
    }
    void step3() override {
        cout << "ConcreteClassB : step3" << endl;
    }
};

#endif /* CONCRETE_CLASS_B_H */