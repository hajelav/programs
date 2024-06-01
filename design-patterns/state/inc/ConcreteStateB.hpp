#ifndef CONCRETE_STATE_B_H
#define CONCRETE_STATE_B_H

#include "AbstractState.hpp"
#include "Context.hpp"
#include "ConcreteStateA.hpp"

//class ConcreteStateA;
class ConcreteStateB : public AbstractState
{

public:
      ConcreteStateB() {} 
      ~ConcreteStateB() {} 

    void handle(Context* context) override {
        cout << "ConcreteStateB handles the request." << endl;
        //AbstractState *stateA = new ConcreteStateA();
        
        context->setState(new ConcreteStateA());
    } 
      
};


#endif // CONCRETE_STATE_B_H