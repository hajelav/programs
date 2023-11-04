#ifndef CONCRETE_SUBSCRIBER_H
#define CONCRETE_SUBSCRIBER_H

#include "AbstractSubscriber.hpp"
#include <iostream>

using namespace std;

class ConcreteSubscriber : public AbstractSubscriber {
    public:
        ConcreteSubscriber(string name) : name(name) {}
        void update(const string& msg) {
            cout << name << " received " << msg << endl;
        }

        string getSubscriberName() {
            return name;
        }

    private:
        string name; //name of Concrete subscriber
};

#endif /* CONCRETE_SUBSCRIBER_H */
