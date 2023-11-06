#ifndef CONCRETE_LIGHTS_ON_COMMAND_H
#define CONCRETE_LIGHTS_ON_COMMAND_H

#include "AbstractCommand.hpp"
#include "Lights.hpp"

class ConcreteLightOnCommand : public AbstractCommand {

    public:
        ConcreteLightOnCommand(Lights* light) {
            this->light = light;
        }
        void execute() {
            light->on();
        }

    private:
        Lights* light;
};
 
#endif /* CONCRETE_LIGHTS_ON_COMMAND_H */
