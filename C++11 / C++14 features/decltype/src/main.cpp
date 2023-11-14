#include <iostream>

// Function with trailing return type
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main() {
    // Using the add function with different types
    int result1 = add(5, 3);       // int + int
    double result2 = add(2.5, 4);   // double + int
    double result3 = add(3, 7.5);   // int + double

    // Displaying results
    std::cout << "Result 1: " << result1 << std::endl; // Result 1: 8
    std::cout << "Result 2: " << result2 << std::endl; // Result 2: 6.5
    std::cout << "Result 3: " << result3 << std::endl; // Result 3: 10.5

    return 0;
}
