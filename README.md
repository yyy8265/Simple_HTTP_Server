# Simple HTTP Server (C++)

一个基于 **C++ 与 POSIX Socket** 实现的简易 HTTP 静态文件服务器，用于学习网络编程、HTTP 协议基础以及模块化 C++ 工程结构。

---

## 功能概述

- 支持 HTTP/1.1 GET 请求
    
- 提供静态文件服务
    
- 可配置监听端口与网站根目录
    
- 多线程并发处理客户端连接
    
- 自动识别常见 MIME 类型
    
- 线程安全日志系统（控制台 + 文件）

---

## 项目结构

```
my_http_server/ 
├── CMakeLists.txt 
├── config.txt                 # 服务器配置文件 
├── README.md 
├── www/                        # 静态文件根目录 
│   ├── index.html 
│   └── test.txt 
│ 
├── include/ 
│   ├── http/                   # HTTP 协议相关 
│   │   ├── HttpParser.h 
│   │   ├── HttpRequest.h 
│   │   └── HttpResponse.h 
│   │ 
│   ├── server/                 # 服务器核心 
│   │   └── HttpServer.h 
│   │ 
│   ├── static/                 # 静态文件服务 
│   │   └── StaticFileHandler.h 
│   │ 
│   └── util/                   # 工具模块 
│       ├── ConfigReader.h 
│       └── Logger.h 
│ 
├── src/                        # 对应实现文件 
│   ├── http/ 
│   ├── server/ 
│   ├── static/ 
│   └── util/ 
│ ├── main.cpp                    # 程序入口 
└── tests/                      # 测试代码     
	└── test_http_parser.cpp
```

---

## 构建与运行

### 构建

`mkdir build cd build cmake .. cmake --build .`

### 运行

`./main`

或指定配置文件路径：

`./main ../config.txt`

浏览器访问：

`http://localhost:8080/`

---

## 配置文件说明

`config.txt` 示例：

`port = 8080 root = ./www`

- `port`：服务器监听端口
    
- `root`：静态文件根目录
    

---

## 模块说明

- `http`：HTTP 请求解析与响应构造
    
- `server`：服务器核心逻辑与连接管理
    
- `static`：静态文件请求处理
    
- `util`：配置读取与日志系统
    

---

## 当前限制

- 仅支持 GET 请求
    
- 不支持 Keep-Alive、HTTPS、动态内容
    
- HTTP 协议解析为简化实现
    

---

## 说明

本项目用于学习和实验，不面向生产环境。