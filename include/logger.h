#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>


class Logger
{
public:
    virtual void log(const std::string& message) = 0;

protected:
    std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};


class FileLogger : public Logger
{
public:
    FileLogger(const std::string& filename) : file(filename, std::ios::app) {}

    void log(const std::string& message) override
    {
        file <<  getCurrentTime() << "  " << message << std::endl;
    }

private:
    std::ofstream file;
};


class ConsoleLogger : public Logger
{
public:
    void log(const std::string& message) override
    {
        std::cout << getCurrentTime() << "  " << message << std::endl;
    }
};

#endif // LOGGER_H
