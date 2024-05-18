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
    DebugLogProcessor(shared_ptr<AbstractLogger> logger) : AbstractLogger(logger) {
        cout << "DebugLogProcessor constructed with next logger " << logger.get() << endl;
        nextLogger = logger;
        
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
            
            cout << "DEBUG " << message << endl;
        } else {
            // If the level is not DEBUG, pass the message to the next logger
            cout << "Cannot handle " << level << " passing to next logger" << endl;
            
            // Call the log function of the next logger in the chain
        if(nextLogger) {
              nextLogger->log(level, message);
        } else {
            cout << "DebugLogProcessor: No next logger, message dropped" << endl;
        }
         
        }
    }


};

#endif /* DEBUG_LOG_PROCESSOR_H */


