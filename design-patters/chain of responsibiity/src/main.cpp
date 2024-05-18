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
 * @param argc The number of command line arguments
 * @param argv An array of strings representing the command line arguments
 * @return 0 indicating successful execution
 */
int main(int argc, const char** argv) {
    std::cout << "Creating logger chain:" << std::endl;
    // Create a chain of loggers: Debug->info->error
    // The logger takes a pointer to the next logger in the chain in its constructor
    // The last logger in the chain should be nullptr
    AbstractLogger *logger = new DebugLogProcessor(new InfoLogProcessor( new ErrorLogProcessor(nullptr)));
    std::cout << "Logger chain created" << std::endl;

    // Log information, error, and debug messages
    // The logger decides which handler to pass the message to based on the log level
    std::cout << "Logging info message:" << std::endl;
    logger->log(AbstractLogger::INFO, "I am info log");
    std::cout << "Info message logged" << std::endl;
    std::cout << "Logging error message:" << std::endl;
    logger->log(AbstractLogger::ERROR, "I am error log");
    std::cout << "Error message logged" << std::endl;
    std::cout << "Logging debug message:" << std::endl;
    logger->log(AbstractLogger::DEBUG, "I am debug log");
    std::cout << "Debug message logged" << std::endl;

    return 0;
}
