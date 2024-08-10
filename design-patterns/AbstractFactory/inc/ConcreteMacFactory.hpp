
// design-patters/AbstractFactory/inc/ConcreteMacFactory.hpp
#ifndef MAC_FACTORY_H
#define MAC_FACTORY_H

#include "AbstractFactory.hpp"
#include "ConcreteMacButton.hpp"
#include <memory>

class MacFactory : public AbstractFactory {
public:
MacFactory() {
    std::cout << "Creating macOS factory\n";
}
    std::shared_ptr<Button> createButton() override {
        return std::make_shared<MacButton>();
    }
};

#endif // MAC_FACTORY_H
