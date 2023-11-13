#ifndef CONCRETE_STATE_A_H
#define CONCRETE_STATE_A_H

#include "AbstractState.hpp"
#include "Context.hpp"
#include "ConcreteStateB.hpp"

class ConcreteStateB;
class ConcreteStateA : public AbstractState
{

public:
    ConcreteStateA() {}
    ~ConcreteStateA() {}

    void handle(Context *context) override {
        cout << "ConcreteStateA handles the request." << endl;
        //transition to a new state if needed
        context->setState(new ConcreteStateB());
    }
};

#endif // CONCRETE_STATE_A_H