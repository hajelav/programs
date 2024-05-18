#ifndef ERROR_LOG_PROCESSOR_H
#define ERROR_LOG_PROCESSOR_H

#include "AbstractLogger.hpp"

class ErrorLogProcessor : public AbstractLogger {

public:
    /**
     * @brief Constructor for ErrorLogProcessor class
     *
     * This constructor initializes the ErrorLogProcessor object
     * with the next logger in the chain of responsibility.
     *
     * @param nextLogger A pointer to the next logger in the chain of responsibility.
     */
ErrorLogProcessor(AbstractLogger* nextLogger) : AbstractLogger(nextLogger) {
    // This constructor is used to initialize the next logger
    // in the chain of responsibility.
}

/**
 * @brief Logs the message if the level is ERROR. Otherwise, passes the message to the next logger.
 *
 * @param level The logging level.
 * @param message The message to be logged.
 */
void log(int level, string message) {
    // If the logging level is ERROR, log the message
    if(level == ERROR) {
        cout << "ERROR " << message << endl;
    } else {
        // If the level is not ERROR, pass the message to the next logger
        cout << "Cannot handle " << level << " passing to next logger" << endl;
        // Call the log function of the next logger in the chain
        nextLogger->log(level, message);
    }
}


};

#endif /* ERROR_LOG_PROCESSOR_H */


