#ifndef CONTEXT_H
#define CONTEXT_H

#include "AbstractState.hpp"

#include <iostream>

using namespace std;

/* the context is the class that can have a number of internal states.
*/
class Context
{
private:
    /* the Context changes its behavior by switching to different states */
    AbstractState *currstate;
public:
    Context() : currstate(nullptr) {}
    ~Context() {}
    void setState(AbstractState *state) {
        currstate = state;
    }
    /* whenever the request is made on the context,
     it is delegated to state to handle */
    void request() {
        if(currstate) {
            currstate->handle(this);
        } else {
            cout << "Context has no state" << endl;
        }
    }

};

#endif /* CONTEXT_H */