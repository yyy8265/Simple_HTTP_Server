#pragma once

#include<string>

//配置文件读取器
class Config
{
public:
    Config();
    Config(const std::string& path);

    uint16_t getPort()const;
    
    std::string getRootDir()const;

private:
    void LoadFromPath(const std::string& path);
    uint16_t port;
    std::string root;
};
