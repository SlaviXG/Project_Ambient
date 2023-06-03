#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * @class Logger
 * @brief An abstract class for logging messages.
 */
class Logger
{
public:
    /**
     * @brief Log a message.
     * @param message The message to be logged.
     */
    virtual void log(const std::string &message) = 0;

protected:
    /**
     * @brief Get the current time as a string.
     * @return The current time as a string in the format "%Y-%m-%d %H:%M:%S".
     */
    std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

/**
 * @class FileLogger
 * @brief A class for logging messages to a file.
 */
class FileLogger : public Logger
{
public:
    /**
     * @brief Construct a FileLogger with a given filename.
     * @param filename The name of the log file.
     */
    FileLogger(const std::string &filename) : file(filename, std::ios::app) {}

    /**
     * @brief Log a message to the file.
     * @param message The message to be logged.
     */
    void log(const std::string &message) override
    {
        file << getCurrentTime() << "  " << message << std::endl;
    }

private:
    std::ofstream file; ///< The log file.
};

/**
 * @class ConsoleLogger
 * @brief A class for logging messages to the console.
 */
class ConsoleLogger : public Logger
{
public:
    /**
     * @brief Log a message to the console.
     * @param message The message to be logged.
     */
    void log(const std::string &message) override
    {
        std::cout << getCurrentTime() << "  " << message << std::endl;
    }
};

#endif // LOGGER_H
