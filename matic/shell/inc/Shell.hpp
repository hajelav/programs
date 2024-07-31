#ifndef SHELL_H

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

/**
 * Class to handle the shell program.
 */
class Shell
{
public:
    /**
     * Constructor.
     */
    Shell() {}

    /**
     * Destructor.
     */
    ~Shell() {}

    /**
     * Runs the shell program, continuously accepting user input until the "exit" command is entered.
     */
    void run();

private:
    /**
     * Execute the given command.
     *
     * @param command The command to execute.
     */
    void execute(const string &command);
};

#endif // !SHELL_H