#include <iostream>
#include "AbstractNewSystemAdapter.hpp"
#include "ConcreteAdapter.hpp"


int main() {

    AbstractNewSystemAdapter *adapter = new ConcreteAdaptor();
    adapter->doNewStuff();

    return 0;
}