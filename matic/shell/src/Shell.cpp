#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>

#include "utils.hpp"
#include "Shell.hpp"

using namespace std;
/**
 * Runs the shell program, continuously accepting user input until the "exit" command is entered.
 *
 * @return void
 *
 * @throws None
 */
void Shell::run()
{
    while (true)
    {
        cout << "$";
        string input;
        getline(cin, input);

        if (input == "exit")
        {
            break;
        }
        // Check for EOF (End-of-File)
        if (cin.eof())
        {
            LOGGER.log(Logger::INFO, "EOF encountered.");
            break;
        }

        // Handle command execution
        execute(input);
    }
}

/**
 * Executes the given command by processing tokens, checking for built-in commands,
 * forking a child process, and handling the execution of the command.
 *
 * @param command The command to be executed.
 *
 * @return void
 *
 * @throws None
 */
void Shell::execute(const string &command)
{
    if (!validateCommand(command))
        return;

    // Parse command into tokens
    vector<string> tokens = parseCommand(command);
    if (!validateTokens(tokens))
        return;

    // strip front and end quotes
    for (size_t i = 0; i < tokens.size(); i++)
    {
        tokens[i] = stripQuotes(tokens[i]);
    }

    // Check for built-in commands
    if (handleBuiltInCommands(tokens))
    {
        return; // Skip the rest of the execution
    }

    // Convert vector<string> to char* array
    vector<char *> args;
    for (const string &token : tokens)
    {
        // string cmd = stripQuotes(token);
        args.push_back(strdup(token.c_str()));
    }
    args.push_back(nullptr); // NULL terminator

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0)
    {
        LOGGER.log(Logger::ERROR, "Error forking process.");
        return;
    }
    else if (pid == 0)
    {
        // Child process
        execvp(args[0], const_cast<char *const *>(args.data()));

        // If execvp returns, it means there was an error
        // LOGGER.log(Logger::ERROR, "Error executing command.");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        // Wait for the child to finish
        int status;
        waitpid(pid, &status, 0);
        // Print the return code of the command if there was and error

        if (static_cast<int>(WEXITSTATUS(status)) != 0)
            LOGGER.log(Logger::ERROR, "Command execution failed.Exit code:" + to_string(WEXITSTATUS(status)));

        // Free allocated memory
        for (char *arg : args)
        {
            free(arg);
        }
    }
}
