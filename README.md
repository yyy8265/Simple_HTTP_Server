# 🧩 Simple C++ HTTP Server

一个基于 **Linux Socket + C++17** 实现的轻量级 HTTP 服务器示例项目，  
重点在于 **清晰的模块拆分、职责划分和可测试设计**。

---

## ✨ 项目特性

- 使用 **TCP Socket** 实现基础 HTTP/1.1 服务
    
- HTTP 请求解析模块 **完全独立**，可单元测试
    
- 服务器逻辑与协议解析 **解耦**
    
- 基于 `std::thread` 的简单并发模型
    
- 使用 **CMake** 构建，结构清晰，易于扩展
    

---

## 📁 项目结构

```
http_server/ 
│ 
├── CMakeLists.txt 
│ 
├── include/ 
│   ├── server/ 
│   │   └── HttpServer.h 
│   │ 
│   └── http/ 
│       ├── HttpRequest.h 
│       ├── HttpResponse.h 
│       └── HttpParser.h 
├── src/ 
│   ├── server/ 
│   │   └── HttpServer.cpp 
│   │ 
│   └── http/ 
│       ├── HttpParser.cpp 
│       └── HttpResponse.cpp 
├── tests/ 
│   └── test_http_parser.cpp 
│ 
└── main.cpp
```

---

## 🧠 模块说明

### HttpServer

- 负责 TCP 监听、连接接收与生命周期管理
    
- 每个客户端连接由独立线程处理
    
- 不参与 HTTP 协议解析
    

### HttpParser

- 负责将原始 HTTP 请求字符串解析为结构化数据
    
- 与 socket、线程完全无关
    
- 支持单元测试
    

### HttpRequest / HttpResponse

- 表示 HTTP 请求与响应的数据结构
    
- 响应通过 `toString()` 序列化为标准 HTTP 报文
    

---

## 🚀 构建与运行

### 1️⃣ 构建项目

`mkdir build cd build cmake .. make`

### 2️⃣ 运行服务器

`./http_server`

浏览器访问：

`http://localhost:8080`

---

## 🧪 单元测试

项目为 `HttpParser` 提供了简单的单元测试（基于 `assert`）：

`./test_http_parser`

测试内容包括：

- HTTP 请求行解析
    
- Header 解析
    
- CRLF 边界处理
    

---

## 🔧 技术栈

- C++17
    
- POSIX Socket（Linux）
    
- CMake
    
- std::thread
    

---

## 📌 后续可扩展方向

- 路由系统（GET /path → handler）
    
- 静态文件服务器
    
- 线程池替代 `std::thread::detach`
    
- 更完整的 HTTP 状态码支持
    
- 使用 epoll 实现高并发模型
    

---

## 📖 项目定位说明

> 本项目是一个 **学习向、工程结构清晰的 HTTP Server 示例**，  
> 重点在于理解：
> 
> - 网络编程基本流程
>     
> - HTTP 报文结构
>     
> - 模块解耦与可测试设计
>