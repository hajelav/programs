#ifndef CONCRETE_ADAPTER_H
#define CONCRETE_ADAPTER_H

#include "AbstractNewSystemAdapter.hpp"
#include "OldSystemAdaptee.hpp"

class ConcreteAdaptor : public AbstractNewSystemAdapter {

    public:
        void doNewStuff() override {
            oldSystem->doOldStuff();
        }
    private:
        OldSystemAdaptee* oldSystem;
        
};

#endif /* CONCRETE_ADAPTER_H */
