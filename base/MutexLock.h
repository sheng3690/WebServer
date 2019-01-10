// @Author Xinde Sheng
// @Email sheng3690@163.com

// Think: How to refactor code if we use C++11 mutex?
#pragma once 
#include<noncopyable.h>
#include<pthread.h>
#include<cstdio>

class MutexLock:public noncopyable
{
public:
    MutexLock()
    {
        pthread_mutex_init(&mutex,NULL)
    }
    ~MutexLock()
    {
        pthread_mutex_lock(&mutex)
        pthread_mutex_destroy(&mutex)
    }
    void lock()
    {
        pthread_mutex_lock(&mutex)
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex)
    }

    // Why return pointer?
    pthread_mutext_t *get(){
        return &mutex;
    }
// friend class regardless of access right
private:
    pthread_mutex_t mutex;
    friend class Condition;
};


class MutexLockGuard: noncopyable
{
public:
    explicit MutexLockGuard(MutexLock &_mutex):mutex(_mutex):
    mutex(_mutex)
    {
        mutex.lock();
    }
    ~MutexLockGuard()
    {
        mutex.unlock();
    }
private:
    MutexLock &mutex;
}