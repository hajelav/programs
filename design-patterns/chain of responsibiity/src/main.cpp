#include <iostream>

#include "AbstractLogger.hpp"
#include "DebugLogProcessor.hpp"
#include "ErrorLogProcessor.hpp"
#include "InfoLogProcessor.hpp"

/*
The Chain of Responsibility is a behavioral design pattern that allows multiple objects to handle a request without explicitly specifying the handler. Instead, each handler in the chain has a reference to the next handler in the chain. When a request is made, it is passed along the chain until it is handled by one of the handlers or reaches the end of the chain.

Components:
Handler Interface: Defines the interface for handling requests. It usually contains a method for handling the request and a reference to the next handler in the chain.

Concrete Handlers: Implement the handler interface and handle specific types of requests. Each concrete handler decides whether to handle the request or pass it to the next handler in the chain.

Client: Initiates requests and passes them to the first handler in the chain. The client is unaware of the internal structure of the chain and does not know which handler will ultimately handle the request.
*/


/**
 * @brief Main function to demonstrate the chain of responsibility pattern
 *        This pattern allows multiple objects to handle a request without explicitly specifying the handler.
 *        The request is passed along the chain of handlers until it is handled by one of them.
 *
 * @param argc The number of command line arguments
 * @param argv An array of strings representing the command line arguments
 *
 * @return 0 indicating successful execution
 *
 * @throws None
 */
int main(int argc, const char** argv) {
    // Create a chain of loggers: errror->info->debug
    // The logger takes a pointer to the next logger in the chain in its constructor
    // The last logger in the chain should be nullptr
    std::cout << "Creating logger chain:" << std::endl;
    
    // Create a chain of loggers with the following order: error -> info -> debug
    // Each logger is linked to the next logger in the chain
    shared_ptr<AbstractLogger> logger = make_shared<ErrorLogProcessor>(
        make_shared<InfoLogProcessor>(
            make_shared<DebugLogProcessor>(nullptr)
        )
    );
    
    std::cout << "Logger chain created" << std::endl;

    // Log information, error, and debug messages
    // The logger decides which handler to pass the message to based on the log level
    logger->log(AbstractLogger::ERROR, "I am error log");

    logger->log(AbstractLogger::INFO, "I am info log");
     
    logger->log(AbstractLogger::DEBUG, "I am debug log");
     logger->log(AbstractLogger::DEFAULT, "I am debug log");
   
    return 0;
}
