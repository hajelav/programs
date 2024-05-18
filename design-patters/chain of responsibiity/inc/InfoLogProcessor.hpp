#ifndef INFO_LOG_PROCESSOR_H
#define INFO_LOG_PROCESSOR_H

#include "AbstractLogger.hpp"

class InfoLogProcessor : public AbstractLogger {

public:
/* when we create an object of debug log processor, we pass the next logger to it*/
InfoLogProcessor(AbstractLogger* nextLogger) : AbstractLogger(nextLogger) {
    cout << "INFO LOG PROCESSOR CREATED" << endl;
}
void log(int level, string message) {
    cout << "INFO LOG PROCESSOR: logging level " << level << ", message " << message << endl;
    if(level == INFO) {
        cout << "INFO LOG PROCESSOR: Message logged" << endl;
        cout << "INFO " << message << endl;
    } else {
        /* if the level is not debug , pass it to the next logger*/
        cout << "INFO LOG PROCESSOR: Level not INFO, passing to next logger" << endl;
        cout << "Cannot handle " << level << " passing to next logger" << endl;
        nextLogger->log(level, message);
    }
}


};

#endif /* INFO_LOG_PROCESSOR_H */


