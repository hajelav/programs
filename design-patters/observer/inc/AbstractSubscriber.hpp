#ifndef ABSTRACT_SUBSCRIBER_H
#define ABSTRACT_SUBSCRIBER_H

#include "AbstractSubscriber.hpp"
#include <iostream>
using namespace std;


class AbstractSubscriber {

    public:
        virtual void update(AbstractSubscriber* subscriber)  = 0;
        virtual string  getSubscriberName();
        
};

#endif /* ABSTRACT_SUBSCRIBER_H */
