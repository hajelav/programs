#ifndef ABSTRACT_TEMPLATE_CLASS_H
#define ABSTRACT_TEMPLATE_CLASS_H

#include <iostream>

using namespace std;

class AbstractTemplateClass {
    public:

        virtual void step1() {
            cout << "AbstractTemplateClass : step 1" << endl;
        }
        virtual void step2() {
            cout << "AbstractTemplateClass : step 2" << endl;
        }
        virtual void step3() {
            cout << "AbstractTemplateClass : step 3" << endl;
        }
        void templateMethod() {
            step1();
            step2();
            step3();
        }
};

#endif /* ABSTRACT_TEMPLATE_CLASS_H */