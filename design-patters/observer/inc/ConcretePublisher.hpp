#ifndef CONCRETE_PUBLISHER_H
#define CONCRETE_PUBLISHER_H

#include "AbstractPublisher.hpp"
#include "AbstractSubscriber.hpp"
#include <vector>

using namespace std;

class ConcretePublisher : public AbstractPublisher {

    public:

        void registerSubscriber(AbstractSubscriber* subscriber) {
            subscribers.push_back(subscriber);
        }

        void removeSubscriber(AbstractSubscriber* subscriber) {

            for(auto it=subscribers.begin(); it != subscribers.end(); it++) {
                if(*it == subscriber) {
                    std::cout << "Subscriber " << subscriber->getSubscriberName() << " removed." << std::endl;
                    subscribers.erase(it);
                }
            }
          
        }

        void notifySubscribers() {
            for(auto &a : subscribers) {
                a->update(a);
            }
        }

    private:
        //maintain a list of subscribers
        vector<AbstractSubscriber*> subscribers; 

    
};

#endif /* CONCRETE_PUBLISHER_H */
