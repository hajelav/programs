#ifndef CONCRETE_ADAPTER_H
#define CONCRETE_ADAPTER_H

#include "AbstractNewSystemAdapter.hpp"
#include "OldSystemAdaptee.hpp"

#include <memory>
#include <iostream>

class ConcreteAdaptor : public AbstractNewSystemAdapter {

    public:
        void doNewStuff() override {
            cout << "New system doing new stuff" << endl;
            oldSystem = make_shared<OldSystemAdaptee>();             oldSystem->doOldStuff();
        }
    private:
        shared_ptr<OldSystemAdaptee> oldSystem;
        
};

#endif /* CONCRETE_ADAPTER_H */
