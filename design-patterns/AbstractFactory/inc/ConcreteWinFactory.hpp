
// Concrete Factories

#ifndef WIN_FACTORY_H
#define WIN_FACTORY_H

#include "AbstractFactory.hpp"
#include "ConcreteWinButton.hpp"
#include <memory>

class WinFactory : public AbstractFactory {
public:
WinFactory() {
    std::cout << "Creating Windows factory\n";
}
    std::shared_ptr<Button> createButton() override {
        return std::make_shared<WinButton>();
    }
};

#endif // WIN_FACTORY_H
