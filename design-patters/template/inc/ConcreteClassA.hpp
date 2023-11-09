#ifndef CONCRETE_CLASS_A_H
#define CONCRETE_CLASS_A_H

#include "AbstractTemplateClass.hpp"
#include  <iostream>

using namespace std;

class ConcreteClassA : public AbstractTemplateClass {

    void step1() override {
        cout << "ConcreteClassA : step1" << endl;
    }
    void step3() override {
        cout << "ConcreteClassA : step3" << endl;
    }
};

#endif /* CONCRETE_CLASS_A_H */