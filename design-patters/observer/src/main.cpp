#include <iostream>
#include "AbstractPublisher.hpp"
#include "ConcretePublisher.hpp"
#include "AbstractSubscriber.hpp"
#include "ConcreteSubscriber.hpp"

int main() {

    //create the publisher
    AbstractPublisher *publisher = new ConcretePublisher("message");

    //create the subscriber 1
    AbstractSubscriber* subscriber1 = new ConcreteSubscriber("subscriber1");
    publisher->registerSubscriber(subscriber1);
     //create the subscriber 2
    AbstractSubscriber* subscriber2 = new ConcreteSubscriber("subscriber2");
    publisher->registerSubscriber(subscriber2);
     //create the subscriber 3
    AbstractSubscriber* subscriber3 = new ConcreteSubscriber("subscriber3");
    publisher->registerSubscriber(subscriber3);

    //publisher notify the subscribers
    publisher->notifySubscribers();
    //unsubscribe subscriber 1
    publisher->removeSubscriber(subscriber1);
    publisher->notifySubscribers();

    
    return 0;
}
