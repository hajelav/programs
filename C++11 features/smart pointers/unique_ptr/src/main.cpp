#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : data(value) {
        std::cout << "Constructing MyClass with value " << value << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructing MyClass with value " << data << std::endl;
    }

    void printData() const {
        std::cout << "Data: " << data << std::endl;
    }

private:
    int data;
};

int main() {
    // Creating a unique_ptr to a MyClass object
    std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>(42);

    // Using the unique_ptr
    uniquePtr->printData();

    // Moving ownership to another unique_ptr (transfer of ownership)
    std::unique_ptr<MyClass> uniquePtr2 = std::move(uniquePtr);

    // uniquePtr is now nullptr as ownership has been transferred
    if (!uniquePtr) {
        std::cout << "uniquePtr is nullptr" << std::endl;
    }

    // The object is automatically deleted when the last unique_ptr owning it is destroyed
    return 0;
}
