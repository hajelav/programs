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
