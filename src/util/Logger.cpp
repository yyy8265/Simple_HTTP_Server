#include"util/Logger.h"
#include<chrono>
#include<ctime>
#include<sstream>
#include<iomanip>

Logger& Logger::instance()
{
    static Logger inst;
    return inst;
}

void Logger::setLogFile(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(mtx);
    if(logfile.is_open())
    {
        logfile.close();
    }

    logfile.open(filename,std::ios::app);
    if(!logfile.is_open())
    {
        std::cerr << "[Logger] Failed to open log file: " << filename << std::endl;
    }
}

Logger::~Logger()
{
    if(logfile.is_open())
    {
        logfile.close();
    }
}

std::string Logger::getLevelString(LogLevel level) 
{
    switch(level) {
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARN";
        case LogLevel::ERROR:   return "ERROR";
        default: return "UNKNOWN";
    }
}

void Logger::log(LogLevel level, const std::string& msg) 
{
    std::lock_guard<std::mutex> lock(mtx);

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    
    std::tm tm_buf{};
#if defined(_WIN32)
    localtime_s(&tm_buf,&t);
#else
    localtime_r(&t,&tm_buf);
#endif


    std::ostringstream oss;
    oss<<std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S")
       <<" [ "<<getLevelString(level)<<" ] "<<msg;

    std::string output=oss.str();

    std::cout<<output<<std::endl;

    if(logfile.is_open())
    {
        logfile<<output<<std::endl;
        logfile.flush();
    }

}

 void Logger::info(const std::string& msg)
{
    log(LogLevel::INFO,msg);
}

void Logger::warn(const std::string& msg)
{
    log(LogLevel::WARNING,msg);
}

void Logger::error(const std::string& msg)
{
    log(LogLevel::ERROR,msg);
}
