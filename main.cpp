#include"server/HttpServer.h"
#include"util/ConfigReader.h"
#include"util/Logger.h"
#include<sstream>
#include<filesystem>

namespace fs = std::filesystem;

int main(int argc,char** argv)
{
    fs::create_directories("./logs");
    Logger::instance().setLogFile("./logs/server.log");

    std::string configPath = "./config.txt";
    if (argc > 1)
    {
        configPath = argv[1];
    }

    Config cfg(configPath);
    
    std::ostringstream oss;
    oss<<"Server starting on port "
       <<cfg.getPort()
       <<", root directory: "
       <<cfg.getRootDir();

    Logger::instance().info(oss.str());
    
    HttpServer server(cfg.getPort(),cfg.getRootDir());
    server.start();

    return 0;
}