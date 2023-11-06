#ifndef CONCRETE_LIGHTS_OFF_COMMAND_H
#define CONCRETE_LIGHTS_OFF_COMMAND_H


#include "AbstractCommand.hpp"
#include "Lights.hpp"

class ConcreteLightOffCommand : public AbstractCommand {

    public:
        ConcreteLightOffCommand(Lights* light) {
            this->light = light;
        }
        void execute() {
            light->off();
        }

    private:
        Lights* light;
};
 
#endif /* CONCRETE_LIGHTS_OFF_COMMAND_H */
