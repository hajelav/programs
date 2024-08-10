#ifndef CONCRETE_PUBLISHER_H
#define CONCRETE_PUBLISHER_H

#include "AbstractPublisher.hpp"
#include "AbstractSubscriber.hpp"
#include <vector>

using namespace std;

class ConcretePublisher : public AbstractPublisher
{
    public:

    ConcretePublisher(string msg) {
        message = msg;
    }

    string getMessage() {
        return message;
    }
    void publish() override
    {
        for(auto &a : subscribers) {
            /* here we are passing the published class pointer instead of a
            string message.This gives us more flexibility , as the subscriber class
            can add more features in the future.*/
            a.first->update(this);
        }
    }

    void registerSubscriber(shared_ptr<AbstractSubscriber> subscriber)
    {
        
        subscribers[subscriber] = true;
        cout << "Subscriber " << subscriber->getSubscriberName() << " registered." << endl;
    };

    void removeSubscriber(shared_ptr<AbstractSubscriber> subscriber)
    {

        /* remove subscriber from the list of subscribers*/
        if (subscribers.count(subscriber) > 0)
        {
            subscribers.erase(subscriber);
        }
        cout << "Subscriber " << subscriber->getSubscriberName() << " removed." << endl;
    }
};

#endif /* CONCRETE_PUBLISHER_H */
