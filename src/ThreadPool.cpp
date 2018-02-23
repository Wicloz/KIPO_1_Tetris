//
// Created by hermes on 22-2-18.
//

#include "../lib/ThreadPool.h"

ThreadPool::ThreadPool(int numThreads) : shutdown(false), jobsPending(0) {
    // Create specified number of threads
    threads.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
        threads.emplace_back(bind(&ThreadPool::threadEntry, this, i));
}

ThreadPool::~ThreadPool() {
    {
        // Unblock any threads and tell them to stop
        unique_lock<mutex> l(lock);
        shutdown = true;
        condVar.notify_all();
    }
    cerr << "Joining threads" << endl;
    for (auto &thread : threads)
        thread.join();
}

void ThreadPool::runMethod(function<void(void)> func) {
    // Place job on the queue and unblock a thread
    unique_lock<mutex> l(lock);

    jobs.emplace(move(func));
    condVar.notify_one();
}

void ThreadPool::threadEntry(int i) {
    function<void(void)> job;
    while (true) {
        {
            unique_lock<mutex> l(lock);

            while (!shutdown && jobs.empty())
                condVar.wait(l);

            if (jobs.empty()) {
                // No jobs to do and we are shutting down
                cerr << "Thread " << i << " terminates" << endl;
                return;
            }

            cerr << "Thread " << i << " does a job" << endl;
            job = move(jobs.front());
            jobs.pop();
        }

        // Do the job without holding any locks
        ++jobsPending;
        job();
        if (--jobsPending == 0)
            mainCondVar.notify_one();
    }
}

bool ThreadPool::done() {
    return jobsPending == 0 && jobs.empty();
}

void ThreadPool::waitUntillDone() {
    if (jobsPending > 0) {
        unique_lock<mutex> l(mainLock);
        mainCondVar.wait(l);
    }

}
