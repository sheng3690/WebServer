// @Author Xinde Sheng
// @Email sheng3690@163.com

# pragma once
#include"noncopyable.h"
#include"MutexLock.h"
#include<pthread.h>
#include<errno.h>
#include<cstdint>
#include<time.h>

/*
int pthread_cond_init(pthread_cond_t *cond, pthred_condattr_t *cond_attr);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_destroy(pthread_cond_t *cond)
int pthread_cond_timewait()
*/

class Condition: public noncopyable
{
public:
    // 
    explicit Condition(MutexLock &_mutex):mutex(_mutex)
    {
        pthread_cond_init(&cond, NULL);//条件变量初始化
    }
    ~Condition()
    [
        pthread_cond_destroy(&cond);//条件变量摧毁
    ]
    void wait()
    {
        pthread_cond_wait(&cond, &mutex);//等待直到被通知
    }
    void notify()
    {
        pthread_cond_signal(&cond);//通知等待
    }
    void notifyAll()
    {
        pthread_cond_broadcast(&cond);//广播通知
    }
    bool waitForSeconds(int seconds)
    {
        // 精确到秒和纳秒
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime); // 获得系统实施时间

        const int64_t kNanoSecondsPerSecond = 1000000000;
        int64_t nanoseconds = static_cast<int64_t>(seconds * kNanoSecondsPerSecond);

        abstime.tv_sec += static_cast<int64_t>(abstime.tv_nsec+nanoseconds) / kNanoSecondsPerSecond);
        abstime.tv_nsec = static_cast<int64_t>(abstime.tv_nsec+nanoseconds) % kNanoSecondsPerSecond);

    }
private:
    pthread_cond_t cond;
    MutexLock mutex
}