#ifndef ABSTRACT_LOGGER_H
#define ABSTRACT_LOGGER_H

#include<iostream>
#include <memory>
using namespace std;

class AbstractLogger {
    public:
        static int INFO;
        static int DEBUG;
        static int ERROR;
        static int DEFAULT;

        AbstractLogger(shared_ptr<AbstractLogger> logger) {
            nextLogger = logger;
        }

        virtual void log(int logLevel, string msg) {
            if(nextLogger != nullptr) {
                nextLogger->log(logLevel, msg);
            }
        }

        //data
        shared_ptr<AbstractLogger> nextLogger;
};

int AbstractLogger::DEBUG = 1;
int AbstractLogger::INFO = 2;
int AbstractLogger::ERROR = 3;
int AbstractLogger::DEFAULT = 0;

#endif /* ABSTRACT_LOGGER_H */
