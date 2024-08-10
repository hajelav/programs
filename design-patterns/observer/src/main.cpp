/*
 * The Observer Pattern is a behavioral design pattern that defines a one-to-many
 * dependency between objects so that when one object changes state, all its
 * dependents are notified and updated automatically.
 *
 * It is often used to implement distributed event handling systems, where the
 * subject (or publisher) maintains a list of observers (or subscribers) and
 * notifies them of any changes in its state.
 */

/* Components: */

// Subject (Observable): Maintains a list of observers and provides methods to
// attach, detach, and notify observers of changes in its state.

// Observer (Subscriber): Defines an interface for receiving updates from the
// subject. Observers register with the subject to receive notifications.

// Concrete Subject: Implements the subject interface and sends notifications
// to observers when its state changes.

// Concrete Observer: Implements the observer interface and defines the
// actions to be taken when notified by the subject.

#include <iostream>
#include <memory>

#include "AbstractPublisher.hpp"
#include "ConcretePublisher.hpp"
#include "AbstractSubscriber.hpp"
#include "ConcreteSubscriber.hpp"

using namespace std;
int main() {

    // Creating the publisher
    shared_ptr<AbstractPublisher> publisher = make_shared<ConcretePublisher>("Hello from publisher");
    /* create the subscribers*/
    shared_ptr<AbstractSubscriber> subscriber1 = make_shared<ConcreteSubscriber>("subscriber1");
    shared_ptr<AbstractSubscriber> subscriber2 = make_shared<ConcreteSubscriber>("subscriber2");
    shared_ptr<AbstractSubscriber> subscriber3 = make_shared<ConcreteSubscriber>("subscriber3");


    publisher->registerSubscriber(subscriber1);
    publisher->registerSubscriber(subscriber2);
    publisher->registerSubscriber(subscriber3);
    publisher->publish();
    publisher->removeSubscriber(subscriber1);
    publisher->publish();


    
    return 0;
}
