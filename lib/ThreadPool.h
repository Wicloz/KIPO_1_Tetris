#ifndef TETRIS_THREADPOOL_H
#define TETRIS_THREADPOOL_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>

using namespace std;

class ThreadPool {
private:
    void threadEntry(int i);

    mutex lock;
    condition_variable condVar;
    bool shutdown;
    queue<function<void(void)>> jobs;
    vector<thread> threads;
    int jobsPending;
    mutex mainLock;
    condition_variable mainCondVar;

public:
    explicit ThreadPool(int numThreads);

    ~ThreadPool();

    void runMethod(function<void(void)> func);

    bool done();

    void waitUntillDone();
};


#endif //THREADPOOL_H
