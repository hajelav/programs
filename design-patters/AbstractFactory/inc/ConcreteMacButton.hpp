
#ifndef MAC_BUTTON_H
#define MAC_BUTTON_H
#include <iostream>
#include "AbstractButton.hpp"
// Concrete Product: Mac Button
// Concrete Product: macOS Button

class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering macOS button\n";
    }
};

#endif // MAC_BUTTON_H
