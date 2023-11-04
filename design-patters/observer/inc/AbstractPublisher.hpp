#ifndef ABSTRACT_PUBLISHER_H
#define ABSTRACT_PUBLISHER_H

#include "AbstractSubscriber.hpp"

class AbstractPublisher {

    public:
        virtual void registerSubscriber(AbstractSubscriber* subsriber) = 0;
        virtual void removeSubscriber(AbstractSubscriber* subscriber) = 0;
        virtual void notifySubscribers() = 0;
        virtual string getMessage() = 0;

};

#endif /* ABSTRACT_PUBLISHER_H */
