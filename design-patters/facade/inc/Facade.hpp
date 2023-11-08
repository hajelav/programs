#ifndef FACADE_H
#define FACADE_H

#include "SubSystemA.hpp"
#include "SubSystemB.hpp"
#include "SubSystemC.hpp"
#include <iostream>

using namespace std;

class Facade {

    public:
        void operation1() {
            cout << ""
            subsystemA->operationA();
            subsystemB->operationB();
        }
        void operation2() {
            subsystemB->operationB();
            subsystemC->operationC();
        }

    private:
        SubSystemA *subsystemA;
        SubSystemB *subsystemB;
        SubSystemC *subsystemC;

};

#endif /* FACADE_H */