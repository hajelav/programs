/*
In C++, closures typically refer to lambdas or anonymous functions introduced in C++11. 
A closure is a function object that has access to variables in its lexical scope, even 
if they are not passed as arguments. Closures provide a way to create inline, unnamed 
functions, which can be convenient in certain situations.
*/

#include <iostream>

int main() {
    int x = 10;

    // Lambda function (closure)
    auto closure = [&]() {
        std::cout << "X (Inside closure): " << x++ << std::endl;
    };

    // Call the closure
    closure();
    std::cout << "X (Outside closure): " << x << std::endl;

    return 0;
}
