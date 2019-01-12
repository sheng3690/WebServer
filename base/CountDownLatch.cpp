// @Author Xinde Sheng
// @Email sheng3690@163.com
#include"CountDownLatch.h"
// Latch中文有插销的意思


CountDownLatch::CountDownLatch(int count)
  :mutex_(),
  condition_(mutex_),
  count_(count_)
{ }

// 让一个或多个线程等待，直到count=0
void CountDownLatch::wait()
{
    MutexLockGuard lock(mutex_); // 对CountDownLatch对象的加锁
    while(count_ > 0)
    {
        condition_.wait();
    }
}

void CountDownLatch::countDown()
{
    MutexLockGuard lock(mutex_);
    --count_;
    if (count_ == 0)
        condition_.notifyAll();
}