#ifndef DEBUG_LOG_PROCESSOR_H
#define DEBUG_LOG_PROCESSOR_H

#include "AbstractLogger.hpp"

class DebugLogProcessor : public AbstractLogger {

public:

/* when we create an object of debug log processor, we pass the next logger to it*/
DebugLogProcessor(AbstractLogger* logger) : AbstractLogger(logger) {}
void log(int level, string message) {
    if(level == DEBUG) {
        cout << "DEBUG " << message << endl;
    } else {
        /* if the level is not debug , pass it to the next logger*/
        cout << "Cannot handle " << level << " passing to next logger" << endl;
        nextLogger->log(level, message);
    }
}


};

#endif /* DEBUG_LOG_PROCESSOR_H */


