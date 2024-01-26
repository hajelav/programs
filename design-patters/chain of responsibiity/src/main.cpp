#include <iostream>

#include "AbstractLogger.hpp"
#include "DebugLogProcessor.hpp"
#include "ErrorLogProcessor.hpp"
#include "InfoLogProcessor.hpp"


int main(int argc, const char** argv) {

    /* create a chain of loggers Debug->info->error*/
    AbstractLogger *logger = new DebugLogProcessor(new InfoLogProcessor( new ErrorLogProcessor(nullptr)));
    logger->log(AbstractLogger::INFO, "I am info log");
    logger->log(AbstractLogger::ERROR, "I am error log");
    logger->log(AbstractLogger::DEBUG, "I am debug log");
    return 0;
}