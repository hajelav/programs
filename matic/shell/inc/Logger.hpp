// Logger.hpp
#pragma once

#include <iostream>
#include <string>
#include <ctime>

using namespace std;
/* Singleton pattern for logger */
class Logger
{
public:
    enum LogLevel
    {
        INFO,
        WARNING,
        ERROR
    };

    static Logger &getInstance()
    {
        static Logger logger;
        return logger;
    }

    /**
     * Logs a message with the specified log level.
     *
     * @param level The log level of the message.
     * @param message The message to be logged.
     *
     * @throws None
     */
    void log(LogLevel level, const string &message)
    {
        string timestamp = getTimestamp();
        string levelStr;

        switch (level)
        {
        case INFO:
            levelStr = "INFO";
            break;
        case WARNING:
            levelStr = "WARNING";
            break;
        case ERROR:
            levelStr = "ERROR";
            break;
        }

        cout << "[" << timestamp << "] [" << levelStr << "] " << message << endl;
    }

private:
    // Private constructor to prevent instantiation from outside
    Logger() {}

    /**
     * Retrieves the current timestamp in the format "%Y-%m-%d %H:%M:%S".
     *
     * @param None
     *
     * @return A string containing the timestamp.
     *
     * @throws None
     */
    string getTimestamp()
    {
        time_t now = time(nullptr);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return string(timestamp);
    }
};
