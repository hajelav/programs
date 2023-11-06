#include <iostream>

#include "Lights.hpp"
#include "InvokerRemoteController.hpp"
#include "AbstractCommand.hpp"
#include "ConcreteLightOffCommand.hpp"
#include "ConcreteLightOnCommand.hpp"

int main() {


    //initialize the controller
    InvokerRemoteController* controller = new InvokerRemoteController();

    //initialize the vendor class 
    Lights *light = new Lights();

    //initilize the turn off command
    AbstractCommand *command1 = new ConcreteLightOffCommand(light);

    //set the command to turn off the lights
    controller->setCommand(command1);
    //execute the command 
    controller->executeCommand();

    //initialize the turn on command
    AbstractCommand *command2 = new ConcreteLightOnCommand(light);

    //set the command to turn off the lights
    controller->setCommand(command2);
    //execute the command 
    controller->executeCommand();



    return 0;
}