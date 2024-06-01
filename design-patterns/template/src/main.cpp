/*
 The Template Method Pattern is a behavioral design pattern that defines the skeleton of an
 algorithm in a method but allows subclasses to provide some or all of the steps. 
 It provides a template for an algorithm and allows variations in
 the implementation of certain steps. 
*/

#include "AbstractTemplateClass.hpp"
#include "ConcreteClassA.hpp"
#include "ConcreteClassB.hpp"

int main() {

    AbstractTemplateClass *templateA = new ConcreteClassA();
    AbstractTemplateClass *templateB = new ConcreteClassB();
    templateA->templateMethod();
    cout << "------------------------------------" << endl;
    templateB->templateMethod();

    delete templateA;
    delete templateB;

    return 0;
}