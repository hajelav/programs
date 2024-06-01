// design-patters/AbstractFactory/inc/ConcreteWinButton.hpp
// Concrete Product: Windows Button
#ifndef WIN_BUTTON_H
#define WIN_BUTTON_H

#include <iostream>
#include "AbstractButton.hpp"

class WinButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows button\n";
    }
};

#endif // WIN_BUTTON_H
