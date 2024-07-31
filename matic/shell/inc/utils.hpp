#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <stack>

#include "LogHelper.hpp"

// Maximum sizes for command and arguments
const int MAX_COMMAND_SIZE = 1000;
const int MAX_ARGS = 100;

using namespace std;

/**
 * A function to strip leading and trailing quotes from a string.
 *
 * @param str The input string from which to strip quotes.
 *
 * @return A string with leading and trailing quotes removed.
 *
 * @throws None
 */
std::string stripQuotes(const std::string &str)
{
    std::string result = str;

    if (!result.empty())
    {
        if (result.front() == '"' || result.front() == '\'')
        {
            result.erase(0, 1); // Remove first character
        }

        if (result.back() == '"' || result.back() == '\'')
        {
            result.pop_back(); // Remove last character
        }
    }

    return result;
}

/**
 * Parses a command string into a vector of arguments.
 *
 * @param command The command string to parse.
 * @return A vector of strings representing the parsed arguments.
 *
 * @throws None
 */
vector<string> parseCommand(const string &command)
{
    vector<string> args;
    string arg;
    char quoteChar = '\0';
    bool inQuotes = false;

    for (char c : command)
    {
        if (!inQuotes && (c == '\'' || c == '"'))
        {
            inQuotes = true;
            quoteChar = c;
            arg += c;
        }
        else if (inQuotes && c == quoteChar)
        {
            inQuotes = false;
            arg += c;
        }
        else if (!inQuotes && c == ' ')
        {
            if (!arg.empty())
            {
                args.push_back(arg);
                arg.clear();
            }
        }
        else
        {
            arg += c;
        }
    }

    if (inQuotes)
    {
        LOGGER.log(Logger::ERROR, "mismatched quotes");
        return {};
    }

    if (!arg.empty())
    {
        args.push_back(arg);
    }

    return args;
}

/**
 * A function to handle built-in commands based on the input tokens.
 *
 * @param tokens A vector of strings representing the command tokens.
 *
 * @return true if the command is handled, false otherwise.
 */
bool handleBuiltInCommands(const vector<string> &tokens)
{

    if (tokens[0] == "cd")
    {
        if (tokens.size() == 1)
        {
            // Change to home directory
            chdir(getenv("HOME"));
        }
        else
        {
            // Change to specified directory
            // tokens[1] = stripQuotes(tokens[1]);

            if (chdir(tokens[1].c_str()) != 0)
            {
                LOGGER.log(Logger::ERROR, "Directory not found.");
                return false;
            }
        }
        return true; // Command handled
    }
    return false; // Command not handled
}

/**
 * Check the total size of the command and log an error if it exceeds the maximum allowed size.
 *
 * @param command The input command to be validated.
 *
 * @return false if the command size exceeds the maximum allowed size, true otherwise.
 *
 * @throws None
 */
bool validateCommand(const string &command)
{
    // Check total command size
    if (command.size() > MAX_COMMAND_SIZE)
    {
        LOGGER.log(Logger::ERROR, "Command size exceeds maximum allowed size.");
        return false;
    }
    return true;
}

    /**
     * Validates the given vector of tokens.
     *
     * @param tokens A vector of strings representing the tokens to be validated.
     *
     * @return true if the tokens are valid, false otherwise.
     *
     * @throws None
     */
bool validateTokens(const vector<string> &tokens)
{
    if (tokens.empty())
        return false;

    // Check number of arguments
    if (tokens.size() > MAX_ARGS)
    {
        LOGGER.log(Logger::ERROR, "Argument length exceeds maximum allowed size.");
        return false;
    }

    return true;
}

#endif
