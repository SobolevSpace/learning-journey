// 提供一个单例模式的实现

// 这里注意,局部static变量的初始化是在第一次使用时进行的

// todo: 带参构造类型的单例模式

#include <iostream>

template <typename T> 
class Singleton {
public:
    static T& GetInstance() {
        static T instance;
        return instance;
    }
    
    Singleton() = default;

private:
    Singleton(const Singleton&) = delete;
    Singleton &operator= (const Singleton&) = delete;
};

class TestType{
public:
    static int construct_count;

    float x;
    int y;

    TestType(float _x = 0.0f, int _y = 0): x(_x), y(_y) {
        ;
        construct_count++; 
    }
};

int TestType::construct_count = 0;

int main() {
    Singleton<TestType> tester;
    void* p = &tester.GetInstance();
    Singleton<TestType> tester2;
    void* p2 = &tester2.GetInstance();

    if (p == p2) {
        std::cout<<"Unit Test Passed."<<std::endl;
        return 0;
    } else {
        std::cout<<"Error: Not Singleton"<<std::endl;
        return -1;
    }
}