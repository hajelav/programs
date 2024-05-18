
#include <iostream>
#include "Singleton.hpp"

#include <iostream>
#include <assert.h>
using namespace std; 
int main() {
    Singleton& singleton1 = Singleton::getInstance();
    Singleton& singleton2 = Singleton::getInstance();

    cout << "singleton1: " << &(singleton1) << endl;
    cout << "singleton2: " << &(singleton2) << endl;
    assert(&singleton1 == &singleton2);
    
    return 0;
}
