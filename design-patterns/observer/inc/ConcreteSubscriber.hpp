#ifndef CONCRETE_SUBSCRIBER_H
#define CONCRETE_SUBSCRIBER_H

#include "AbstractSubscriber.hpp"
#include "AbstractPublisher.hpp"
#include <iostream>

using namespace std;

class ConcreteSubscriber : public AbstractSubscriber {
    public:
        ConcreteSubscriber(string n) : name(n) {}

        void update(AbstractPublisher* publisher) {
            cout << getSubscriberName() << " received  message : " << publisher->getMessage() << endl;
        }

        string getSubscriberName() {
            return name;
        }

    private:
        string name; //name of Concrete subscriber
};

#endif /* CONCRETE_SUBSCRIBER_H */
