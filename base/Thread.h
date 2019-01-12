// @Author Xinde Sheng
// @Email sheng3690@163.com
#pragma once
#include"CountDownLatch.h"
#include"noncopyable.h"
#include<functional>
#include<memory>
#include<pthread.h>
#include<string>
#include<sys/syscall.h>
#include<unistd.h>



class Thread:public noncopyable
{
public:
    typedef std::function<void ()> ThreadFunc; //std::function是类模板
    explicit Thread(const ThreadFunc&, )
    void start();
    int join();
    
    bool started() const { return str}
    pid_t tid();
    const string& name();
private:
    void setDefaultName();
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    CountDownLatch latch_;
};