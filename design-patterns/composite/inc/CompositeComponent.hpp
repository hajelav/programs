#ifndef COMPOSITE_COMPONENT_H
#define COMPOSITE_COMPONENT_H

#include "AbstractComponent.hpp"
#include <vector>
#include <iostream>


using namespace std;

class CompositeComponent : public AbstractComponent {

private:
    vector<AbstractComponent*> children;
    string name;

public:
    CompositeComponent(string name) : name(name) {}

    void add(AbstractComponent* component) {
        children.push_back(component);
    }

    void operation() {
        cout << "Composite operation: " << name << endl;
        for(auto &a : children) { 
            a->operation();
        }
    }

    
    ~CompositeComponent() {
        for(auto &a : children) {
            delete a;
        }
    }
};




#endif /* COMPOSITE_COMPONENT_H */
