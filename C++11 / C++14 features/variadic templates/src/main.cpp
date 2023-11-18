#include <iostream>

using namespace std;

// Base case for the recursive template function
int sum() {
    return 0; // Return 0 when there are no more arguments
}

// Recursive template function to compute the sum of variable arguments
template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...); // Recur with the rest of the arguments
}

int main() {
    // Example usage of the variadic template function
    int result = sum(1, 2, 3, 4, 5);
    std::cout << "Sum: " << result << std::endl;

    double result2 = sum(1.1, 2.2, 3.3, 4.4, 5.5);
    std::cout << "Sum: " << result2 << std::endl;

    return 0;
}
