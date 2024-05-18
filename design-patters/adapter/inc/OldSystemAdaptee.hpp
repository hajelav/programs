#ifndef OLD_SYSTEM_ADAPTEE_H
#define OLD_SYSTEM_ADAPTEE_H

#include <iostream>

using namespace std;

class OldSystemAdaptee {
    public:
        void doOldStuff() {
            cout << "Called from New interface. Old system doing old stuff" << endl;
        }
};

#endif /* OLD_SYSTEM_ADAPTEE_H */
