// @Author Xinde Sheng
// @Email sheng3690@163.com

#pragma once 
class noncopyable
{
protected:
    noncopyable(){}
    ~noncopyable(){}
private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};
// 要写一个单例类，就要在类中作如下声明，
// 把他们的构造函数和析构函数声明为protected
// 把他们的拷贝构造函数和赋值函数声明为private
// noncopyable的意思就是不可拷贝的类，如果想声明一个类为单例类，就
// 直接让其public集成noncopyable

