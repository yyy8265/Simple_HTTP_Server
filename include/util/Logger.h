#pragma once
#include<string>
#include<mutex>
#include<fstream>
#include<iostream>

enum class LogLevel
{
    INFO,
    WARNING,
    ERROR
};

class Logger
{
public:
    static Logger& instance();

    void setLogFile(const std::string& filename);

    void log(LogLevel level,const std::string& msg);

    void info(const std::string& msg);
    
    void warn(const std::string& msg);

    void error(const std::string& msg);

private:
    Logger()=default;
    ~Logger();

    Logger(const Logger&)=delete;
    Logger& operator= (const Logger&)=delete;
    std::string getLevelString(LogLevel level);

    std::mutex mtx;
    std::ofstream logfile;

};