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
    // Because pthread_cond_wait and pthread_cond_timewait in Condition.h need pointer
    pthread_mutext_t *get(){
        return &mutex;
    }
// friend class regardless of access right
private:
    pthread_mutex_t mutex;
    friend class Condition;
};

// 
class MutexLockGuard: public noncopyable
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

// MutexLock封装临界区，这是一个简单的资源类，用RAII（资源获取就是初始化）手法封装互斥器的创建与销毁。
// MutexLock一般是别的class的数据成员
// MutexLockGaurd封装临界区的进入和退出，即加锁和解锁。MutexLockGaurd一般是个栈上的对象，他的作用域刚好等于
// 等于临界区域
// MutexLockGaurd类使用RAII技法封装，在实际应用中这个类更常用，作为class数据成员的MuterLock
// 只能用于同步本class的其他数据成员的读和写，他不能把他们安全的析构。因为当对象析构时MuterLock也。
// 使用方法，两者配合，先使用MutexLock定义一个临界区，然后该MutexLock作为参数传进MutexLockGuard对象。

