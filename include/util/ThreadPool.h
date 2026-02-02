#pragma once

#include <cstddef>
#include <functional>
#include<vector>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<atomic>

class ThreadPool
{
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> workers;

    std::queue<std::function<void()>> tasks;

    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> stop;

};