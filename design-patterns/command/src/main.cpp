/*
The Command Pattern is a behavioral design pattern that encapsulates a request as an object,
 thereby allowing parameterization of clients with queues, requests, and operations.
 It decouples the sender of a request from the receiver, allowing requests to be treated as
 objects that can be stored, passed, and executed later.

Components:
Command: Interface for all concrete command classes. It declares a method for executing the command.

Concrete Command: Implements the Command interface and defines the binding between a Receiver object and an action. It invokes the corresponding operation(s) on the Receiver.

Receiver: Knows how to perform the operations associated with carrying out the request. It is invoked by the Concrete Command when the command is executed.

Invoker: Requests the command to carry out an operation. It holds the command object and invokes the command by calling its execute method.
*/

#include <iostream>

#include "Lights.hpp"
#include "InvokerRemoteController.hpp"
#include "AbstractCommand.hpp"
#include "ConcreteLightOffCommand.hpp"
#include "ConcreteLightOnCommand.hpp"

using namespace std;

int main()
{

    // initialize the controller
    InvokerRemoteController *controller = new InvokerRemoteController();

    // initialize the vendor class
    Lights *light = new Lights();

    // initilize the turn off command
    AbstractCommand *command1 = new ConcreteLightOffCommand(light);

    // set the command to turn off the lights
    controller->setCommand(command1);
    // execute the command
    controller->executeCommand();

    // initialize the turn on command
    AbstractCommand *command2 = new ConcreteLightOnCommand(light);

    // set the command to turn on the lights
    controller->setCommand(command2);
    // execute the command
    controller->executeCommand();

    // undo the last command
    controller->undoLastCommand();
    // undo the last comman again
    controller->undoLastCommand();
    // undo the last command
    controller->undoLastCommand();

    return 0;
}