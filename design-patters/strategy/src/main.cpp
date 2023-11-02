#include <iostream>
#include "mylib.h"

int main() {
    std::cout << "Hello, CMake Tutorial!" << std::endl;
    int result = add(5, 7);
    std::cout << "5 + 7 = " << result << std::endl;
    return 0;
}
