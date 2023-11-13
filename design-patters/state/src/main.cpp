/*
The State Pattern is a behavioral design pattern that allows an object to alter its 
behavior when its internal state changes. The object will appear to change its class. 
Here's a simple example of the State 
Pattern in C++
*/

#include "Context.hpp"
#include "ConcreteStateB.hpp"
#include "ConcreteStateA.hpp"

int main() {
    //create a context
    Context *context = new Context();

    //set the intial state of the context as ConcreteStateA
    context->setState(new ConcreteStateA());

    //perform request() on context to change the states
    context->request();

    context->request();

    context->request();

    return 0;
}