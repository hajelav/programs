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
    // Creating a shared_ptr to a MyClass object
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(42);

    // Using the shared_ptr
    sharedPtr->printData();

    // Creating another shared_ptr that shares ownership with the first one
    std::shared_ptr<MyClass> sharedPtr2 = sharedPtr;

    // Both shared_ptrs share ownership of the same object
    std::cout << "Use count: " << sharedPtr.use_count() << std::endl;

    // The object is automatically deleted when the last shared_ptr owning it is destroyed
    return 0;
}
