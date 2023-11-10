#include <iostream>
#include <utility>

// A function that processes the lvalue argument
void process(int& x) {
    std::cout << "Lvalue reference: " << x << std::endl;
}
// A function that processes the rvalue argument
void process(int&& x) {
    std::cout << "Rvalue reference: " << x << std::endl;
}

// Function template with a universal reference (forwarding refernce) parameter
template <typename T>
void myFunction(T&& arg) {
    // std::forward is used to forward the argument with the correct value category
    process(std::forward<T>(arg));
}


int main() {
    int a = 42;

    // 'a' is an lvalue
    myFunction(a);

    // 10 is an rvalue
    myFunction(10);

    return 0;
}
