// @Author Xinde Sheng
// @Email sheng3690@163.com

# pragma once 
#include"MutexLock.h"
#include"Condition.h"
#include"noncopyable.h"

// CoutDownLatch function?
// 参考Java的一个同步辅助类，在完成一组正在执行的操作之前，它允许一个或多个线程一直等待。
// 

class CoutDownLatch
{
public:
    explicit CoutDownLatch(int count);
    void wait();
    void countDown();
private:
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
}