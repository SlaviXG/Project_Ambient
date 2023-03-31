#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>>
#include <fstream>


class Logger
{
public:
    virtual void log(const std::string& message) = 0;
};


class FileLogger : public Logger
{
public:
    FileLogger(const std::string& filename) : file(filename, std::ios::app) {}

    void log(const std::string& message) override
    {
        file << message << std::endl;
    }

private:
    std::ofstream file;
};


class ConsoleLogger : public Logger
{
public:
    void log(const std::string& message) override
    {
        std::cout << message << std::endl;
    }
};

#endif // LOGGER_H
