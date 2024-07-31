#include "Shell.hpp"
#include "LogHelper.hpp"
/**
 * Handles a signal by printing the received signal number and waiting for all
 * terminated child processes to finish.
 *
 * @param signal The signal number that was received.
 *
 * @return void
 *
 * @throws None
 */
void handleSignal(int signal)
{
    switch (signal)
    {
    case SIGINT:
        LOGGER.log(Logger::INFO, "Received SIGINT signal: User pressed Ctrl+C.");
        break;
    case SIGTERM:
        LOGGER.log(Logger::INFO, "Received SIGTERM signal: User pressed Ctrl+\\.");
        break;

    default:
        LOGGER.log(Logger::ERROR, "Unknown signal received.");
        break;
    }
    
}

/**
 * The main function of the program.
 *
 * @return 0 indicating successful execution
 */
int main() {

    // Register signal handlers
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);
    
    Shell shell;
    LOGGER.log(Logger::INFO, "Starting shell...");
    shell.run();
    LOGGER.log(Logger::INFO, "Exiting shell...");
    return 0;
}