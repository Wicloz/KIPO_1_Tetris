//
// Created by hermes on 22-2-18.
//

#ifndef KIPO_1_TETRIS_THREADPOOL_H
#define KIPO_1_TETRIS_THREADPOOL_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

using namespace std;

class ThreadPool {
private:
    void threadEntry(int i);

    mutex lock;
    condition_variable condVar;
    bool shutdown;
    queue<function<void(void)>> methods;
    vector<thread> threads;

public:
    ThreadPool(int numThreads);

    ~ThreadPool();

    void runMethod(function<void(void)> func);
};


#endif //KIPO_1_TETRIS_THREADPOOL_H
