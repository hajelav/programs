#ifndef ERROR_LOG_PROCESSOR_H
#define ERROR_LOG_PROCESSOR_H

#include "AbstractLogger.hpp"

class ErrorLogProcessor : public AbstractLogger {

public:
/* when we create an object of debug log processor, we pass the next logger to it*/
ErrorLogProcessor(AbstractLogger* nextLogger) : AbstractLogger(nextLogger) {}
void log(int level, string message) {
    if(level == ERROR) {
        cout << "ERROR " << message << endl;
    } else {
        /* if the level is not error , pass it to the next logger*/
        cout << "Cannot handle " << level << " passing to next logger" << endl;
        nextLogger->log(level, message);
    }
}


};

#endif /* ERROR_LOG_PROCESSOR_H */


