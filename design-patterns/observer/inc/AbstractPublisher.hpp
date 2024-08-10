#ifndef ABSTRACT_PUBLISHER_H
#define ABSTRACT_PUBLISHER_H

#include "AbstractSubscriber.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <map>

using namespace std;
class AbstractPublisher
{

public:
    
    virtual void publish() = 0;
    virtual void registerSubscriber(shared_ptr<AbstractSubscriber> subscriber) = 0;
    virtual void removeSubscriber(shared_ptr<AbstractSubscriber> subscriber) = 0;
    virtual string getMessage() = 0;
    //virtual void notifySubscribers() = 0;


    string message;
    map<shared_ptr<AbstractSubscriber>, bool> subscribers;
};

#endif /* ABSTRACT_PUBLISHER_H */
