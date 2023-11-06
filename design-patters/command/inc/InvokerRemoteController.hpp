#ifndef INVOKER_REMOTE_CONTROLLER_H
#define INVOKER_REMOTE_CONTROLLER_H

#include "AbstractCommand.hpp"

class InvokerRemoteController {

    public:
    void setCommand(AbstractCommand* command) {
        this->command = command;
    }

    void executeCommand() {
        command->execute();
    }

    private: 
        AbstractCommand* command;

};

#endif /* INVOKER_REMOTE_CONTROLLER_H */
