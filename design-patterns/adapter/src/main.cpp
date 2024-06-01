#include <iostream>
#include "AbstractNewSystemAdapter.hpp"
#include "ConcreteAdapter.hpp"
#include <memory>

using namespace std;

int main() {

    unique_ptr<AbstractNewSystemAdapter> adapter = make_unique<ConcreteAdaptor>();
    adapter->doNewStuff();

    return 0;
}