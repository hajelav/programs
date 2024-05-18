#ifndef DEBUG_LOG_PROCESSOR_H
#define DEBUG_LOG_PROCESSOR_H

#include "AbstractLogger.hpp"

class DebugLogProcessor : public AbstractLogger {

public:

    /**
     * @brief Constructor for DebugLogProcessor class
     *
     * This constructor initializes the DebugLogProcessor object
     * with the next logger in the chain of responsibility.
     *
     * @param logger A pointer to the next logger in the chain of responsibility.
     */
    /**
     * @brief Initializes the DebugLogProcessor object with the next logger
     *
     * @param logger A pointer to the next logger in the chain of responsibility.
     */
    DebugLogProcessor(AbstractLogger* logger) : AbstractLogger(logger) {
        cout << "DebugLogProcessor constructed with logger " << logger << endl;
    }
    /**
     * @brief Logs the message if the level is DEBUG. Otherwise, passes the message to the next logger.
     *
     * @param level The logging level.
     * @param message The message to be logged.
     */
    void log(int level, string message) {
        cout << "DebugLogProcessor log called with level " << level << " and message " << message << endl;
        if(level == DEBUG) {
            // Log message if the level is DEBUG
            cout << "DEBUG - Logging message: " << message << endl;
            cout << "DEBUG " << message << endl;
        } else {
            // If the level is not DEBUG, pass the message to the next logger
            cout << "Cannot handle " << level << " passing to next logger" << endl;
            cout << "Next logger log called with level " << level << " and message " << message << endl;
            nextLogger->log(level, message);
        }
    }


};

#endif /* DEBUG_LOG_PROCESSOR_H */


