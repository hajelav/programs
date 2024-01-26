#ifndef INFO_LOG_PROCESSOR_H
#define INFO_LOG_PROCESSOR_H

#include "AbstractLogger.hpp"

class InfoLogProcessor : public AbstractLogger {

public:
/* when we create an object of debug log processor, we pass the next logger to it*/
InfoLogProcessor(AbstractLogger* nextLogger) : AbstractLogger(nextLogger) {}
void log(int level, string message) {
    if(level == INFO) {
        cout << "INFO " << message << endl;
    } else {
        /* if the level is not debug , pass it to the next logger*/
        cout << "Cannot handle " << level << " passing to next logger" << endl;
        nextLogger->log(level, message);
    }
}


};

#endif /* INFO_LOG_PROCESSOR_H */


