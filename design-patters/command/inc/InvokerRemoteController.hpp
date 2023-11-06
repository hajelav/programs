#ifndef INVOKER_REMOTE_CONTROLLER_H
#define INVOKER_REMOTE_CONTROLLER_H

#include "AbstractCommand.hpp"
#include <vector>
#include <memory> // for shared pointer

using namespace std;

class InvokerRemoteController {

    public:
    void setCommand(AbstractCommand* command) {
        this->command = command;
    }

    void executeCommand() {
        command->execute();
        //whenever we execute the commmand , we also push it to history
        history.push_back(command);
    }

    void undoLastCommand() {
        //check if history is not empty
        if(!history.empty()) {
            //call the undo function of the actual concrete command
                history.back()->undo();
                //pop that command from the history
                history.pop_back();
        } else {
            cout << "Command history is empty" << endl;
        }
    }

    private: 
        AbstractCommand* command;
        vector<AbstractCommand*> history;

};

#endif /* INVOKER_REMOTE_CONTROLLER_H */
