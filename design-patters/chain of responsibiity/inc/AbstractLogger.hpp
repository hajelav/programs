#ifndef ABSTRACT_LOGGER_H
#define ABSTRACT_LOGGER_H

#include<iostream>
 using namespace std;

class AbstractLogger {
    public:
        static int INFO;
        static int DEBUG;
        static int ERROR;

        AbstractLogger(AbstractLogger* logger) {
            nextLogger = logger;
        }

        virtual void log(int logLevel, string msg) {
            if(nextLogger != nullptr) {
                nextLogger->log(logLevel, msg);
            }
        }

        //data
        AbstractLogger* nextLogger;
};

int AbstractLogger::INFO = 1;
int AbstractLogger::DEBUG = 2;
int AbstractLogger::ERROR = 3;

#endif /* ABSTRACT_LOGGER_H */
