#ifndef ABSTRACT_STATE_H
#define ABSTRACT_STATE_H

//#include "Context.hpp"

//forward declaration 
class Context;
class AbstractState {
   
public:
    virtual void handle(Context *context) = 0;
    AbstractState();
    ~AbstractState();
};

#endif /* ABSTRACT_STATE_H */