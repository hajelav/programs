#include <iostream>
#include <memory>
#include "ConcreteMacFactory.hpp"
#include "ConcreteWinFactory.hpp"

// Explanation:
// This code represents the client code in an Abstract Factory design pattern.
// It creates a Windows factory that produces Windows-specific UI components.
// It then uses the factory to create a button and renders it.
int main() {
    // Create a Windows factory
    std::shared_ptr<AbstractFactory> factory = std::make_shared<WinFactory>();

    // Create a button using the factory.WinFactory creates a Windows button
    std::shared_ptr<Button> button = factory->createButton();
    button->render();

    std::shared_ptr<AbstractFactory> macFactory = std::make_shared<MacFactory>();
    std::shared_ptr<Button> macButton = macFactory->createButton();
    macButton->render();
    return 0;
}