/* The Facade Pattern is a structural design pattern that provides a simplified and unified interface to a 
set of interfaces in a subsystem, making it easier to use and understand. It hides the complexities of the 
subsystem and provides a higher-level, simplified interface for the client. Here's a simple example of the
 Facade Pattern in C++:
cpp */

#include "SubSystemA.hpp"
#include "SubSystemB.hpp"
#include "SubSystemC.hpp"
#include "Facade.hpp"
int main() {
    // Client code uses the Facade to interact with the subsystem
    Facade *facade = new Facade();

    //using simplified interface provided by facade
    facade->operation1();
    cout << "-----------------------------------------------" << endl;
    facade->operation2();

    return 0;
}
