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
ErrorLogProcessor(shared_ptr<AbstractLogger> nextLogger) : AbstractLogger(nextLogger) {
    cout << "ErrorLogProcessor constructed with next logger " << nextLogger.get() << endl;
}

/**
 * @brief Logs the message if the level is ERROR. Otherwise, passes the message to the next logger.
 *
 * @param level The logging level.
 * @param message The message to be logged.
 */
void log(int level, string message) {
    // Print the log level and message before processing
    cout << "ErrorLogProcessor: Logging level " << level << ", message " << message << endl;

    // If the logging level is ERROR, log the message
    if(level == ERROR) {
        cout << "ERROR " << message << endl;
    } else {
        // If the level is not ERROR, pass the message to the next logger
        cout << "ErrorLogProcessor: Level not ERROR, passing to next logger" << endl;
         nextLogger->log(level, message);

        
    }
}


};

#endif /* ERROR_LOG_PROCESSOR_H */


