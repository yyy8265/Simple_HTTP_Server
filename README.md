# My HTTP Server（C++）

一个基于 C++17 和 POSIX Socket 实现的轻量级静态 HTTP 服务器，采用线程池模型处理并发连接。
该项目以学习和工程实践为目标，重点关注代码结构、健壮性、安全性和可维护性。

## 项目特性
* 基于 TCP Socket 的 HTTP/1.1 静态文件服务器
* 支持 GET 请求方法
* 使用线程池处理并发客户端连接
* 支持配置监听端口和静态文件根目录
* 根据文件扩展名自动设置 Content-Type
* 基于 std::filesystem::canonical 的路径规范化，防止目录穿越攻击
* 线程安全的日志系统（支持输出到文件）
* 对异常请求和错误场景进行防御性处理

## 项目结构
```
my_http_server/
├── include/            # 头文件
│   ├── http/           # HTTP 请求 / 响应 / 解析
│   ├── server/         # HTTP 服务器核心逻辑
│   ├── static/         # 静态文件处理
│   └── util/           # 配置、日志、线程池等通用模块
│
├── src/                # 源文件实现
│
├── www/                # 静态资源目录
│   ├── index.html
│   └── test.txt
│
├── tests/              # 测试代码（解析器等）
├── config.txt          # 配置文件
├── main.cpp            # 程序入口
└── CMakeLists.txt
```

## 架构说明

* HttpServer
	负责 socket 创建、监听、accept
	将客户端连接分发到线程池
* ThreadPool
	固定数量工作线程
	任务队列 + 条件变量实现同步
* HttpParser
	将原始 HTTP 请求字符串解析为结构化请求对象
* StaticFileHandler
	处理静态文件请求
	执行路径合法性校验
* Logger
	线程安全单例日志器
	支持控制台和文件输出

## 构建方式
### 环境要求
* Linux
* GCC / Clang（支持 C++17）
* CMake ≥ 3.10
### 编译
	mkdir build
	cd build
	cmake ..
	cmake --build .
### 运行方式
	./http_server
或指定配置文件路径：
	`./http_server ../config.txt`

## 配置文件说明（config.txt）
```
# 服务器监听端口
port=8080

# 静态文件根目录
root=./www
```

## 测试示例
`curl http://localhost:8080/`
`curl http://localhost:8080/test.txt`

## 已知限制
* 仅支持 HTTP GET 方法
* 不支持长连接（Keep-Alive）
* 不支持 HTTPS
* 未实现 chunked 编码

## 学习与实践要点
本项目主要用于练习和理解：
* Linux 网络编程（socket / bind / listen / accept）
* 多线程与线程池设计
* HTTP 协议基础
* 文件系统安全（路径规范化）
* 防御式编程与异常处理
* 工程级代码组织与模块划分

## 后续计划（未实现）
* 使用 epoll 的事件驱动模型
* 支持 HTTP Keep-Alive
* 更完善的单元测试
* 更严格的 HTTP 协议校验
