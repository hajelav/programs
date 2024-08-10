#include <iostream>
#include <memory>

class Node
{
public:
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // Use weak_ptr to avoid a cyclic reference

    Node(const std::string &name) : name(name)
    {
        std::cout << "Node " << name << " created\n";
    }
    ~Node()
    {
        std::cout << "Node " << name << " destroyed\n";
    }
};

int main()
{
    std::shared_ptr<Node> node1 = std::make_shared<Node>("Node1");
    std::shared_ptr<Node> node2 = std::make_shared<Node>("Node2");

    // Setting up the cycle
    node1->next = node2;
    node2->prev = node1; // This is a weak_ptr

    // Shared ptr count of Node1 is 1 because , it is  weakly pointed by node2
    std::cout << "Node1 use_count: " << node1.use_count() << std::endl; // 1

    // Shared ptr count of Node2 is 2 because , it is also pointed by node1
    std::cout << "Node2 use_count: " << node2.use_count() << std::endl; // 2

    if (auto sharedPrev = node2->prev.lock())
    { // lock to obtain a shared_ptr
        std::cout << "Node2's prev node is: " << sharedPrev->name << std::endl;
    }

    node2->prev.reset(); // Optional: Reset the weak_ptr

    node2.reset(); // node2 is destroyed here because there is no cycle
    node1.reset(); // node1 is destroyed here

    // After both shared_ptrs are reset, the nodes are destroyed
    return 0;
}
