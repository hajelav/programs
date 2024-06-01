#ifndef CONCRETE_LIGHTS_OFF_COMMAND_H
#define CONCRETE_LIGHTS_OFF_COMMAND_H


#include "AbstractCommand.hpp"
#include "Lights.hpp"

using namespace std;

class ConcreteLightOffCommand : public AbstractCommand {

    public:
        ConcreteLightOffCommand(Lights* light) {
            this->light = light;
        }
        void execute() {
            light->off();
        }

        //undo is just opposite of this command
        void undo() {
            cout << "undo action of light off" << endl;
            light->on();
        }

    private:
        Lights* light;
};
 
#endif /* CONCRETE_LIGHTS_OFF_COMMAND_H */
