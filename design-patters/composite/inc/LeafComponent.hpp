#ifndef LEAF_COMPONENT_H
#define LEAF_COMPONENT_H

#include "AbstractComponent.hpp"
#include <iostream>

using namespace std;

class LeafComponent : public AbstractComponent {

    private: 
        string name;
    
    public:
        LeafComponent(string name) : name(name) {}
        void operation() override {
            cout << "Leaf operation: " << name << endl;
        }
};


#endif /* LEAF_COMPONENT_H */