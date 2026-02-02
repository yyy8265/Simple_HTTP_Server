#include"util/ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads):stop(false)
{
    for(size_t i=0;i<numThreads;++i)
    {
        workers.emplace_back([this]{
            while(true)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->mtx);

                    this->cv.wait(lock,[this]{
                        return stop||!tasks.empty();
                    });

                    if(stop&&tasks.empty())
                    {
                        return;
                    }

                    task=std::move(tasks.front());
                    tasks.pop();
                }
                try
                {
                    task();
                }
                catch(...)
                {                }        
            }   
        });
    }
}

ThreadPool::~ThreadPool()
{
    stop=true;
    cv.notify_all();
    for(auto& t:workers)
    {
        if(t.joinable())
        {
            t.join();
        }
    }
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push(std::move(task));
    }

    cv.notify_one();
}