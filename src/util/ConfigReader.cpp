#include"util/ConfigReader.h"
#include"util/Logger.h"

#include<fstream>
#include<sstream>
#include<algorithm>
#include<iostream>

Config::Config():port(8080),root("./www")
{
    Logger::instance().info(
        "Config initialized with default values: port=8080, root=./www"
    );
}

Config::Config(const std::string& path):port(8080),root("./www")
{
    Logger::instance().info(
        "Config initialized with default values, loading from: " + path
    );
    LoadFromPath(path);
}

uint16_t Config::getPort() const
{
    return port;
}

std::string Config::getRootDir() const
{
    return root;
}

void Config::LoadFromPath(const std::string& path)
{
    std::ifstream file(path);
    if(!file)
    {
        Logger::instance().warn(
            "Config file not found: " + path +
            ", using default settings"
        );
        return;
    }

    Logger::instance().info("Loading config file: " + path);

    std::string line;
    while(std::getline(file,line))
    {
        line.erase(0,line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t")+1);

        if(line.empty()||line[0]=='#')
            continue;
        
        auto pos=line.find('=');
        if(pos==std::string::npos)
        {
            Logger::instance().warn(
                "Invalid config line (missing '='): " + line
            );
            continue;
        }

        
        std::string key=line.substr(0,pos);
        std::string value=line.substr(pos+1);

        key.erase(0,key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t")+1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t")+1);

        if(key=="port")
        {
            try
            {
		int p=std::stoi(value);
		if(p<=0||p>65535)
		{
			throw std::out_of_range("port out of range");
		}
                port=static_cast<uint16_t>(p);

                Logger::instance().info(
                    "Config: port set to " + std::to_string(port)
                );
            }
            catch(...)
            {
                Logger::instance().error(
                    "Invalid port value in config: " + value
                );
            }
        }
        else if(key=="root")
        {
            root=value;
            Logger::instance().info(
                "Config: root directory set to " + root
            );
        }
        else
        {
            Logger::instance().warn(
                "Unknown config key: " + key
            );
        }
    }
    Logger::instance().info("Config file loaded successfully");
}
