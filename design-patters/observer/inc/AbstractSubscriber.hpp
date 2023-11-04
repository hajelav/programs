#ifndef ABSTRACT_SUBSCRIBER_H
#define ABSTRACT_SUBSCRIBER_H

#include "AbstractSubscriber.hpp"
#include "AbstractPublisher.hpp"
#include <iostream>
using namespace std;

class AbstractPublisher;

class AbstractSubscriber {

    public:
        virtual void update(AbstractPublisher* publisher) = 0;
        virtual string getSubscriberName() = 0;
        
};

#endif /* ABSTRACT_SUBSCRIBER_H */
