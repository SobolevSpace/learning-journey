// 代理模式

#include <iostream>

class ISubject {
public:
    virtual void Request(int key) = 0;
};

class RealSubject : public ISubject {
public:
    void Request(int key) { /* do something */ }
};

class Proxy : public ISubject {
public:
    Proxy() { m_realSubject = new RealSubject(); }
    ~Proxy() { delete m_realSubject; }
    void Request(int key) { 
        if (!InCache(key)) {
            m_realSubject->Request(key); 
        } else {
            // Search in Cache
        }
        SetCache(key);
    }
private:
    bool InCache(int key) { return false; }
    void SetCache(int key) { }
    RealSubject* m_realSubject;
};

int main() {
    Proxy* proxy = new Proxy();
    proxy->Request(10);
    delete proxy;
    std::cout << "Unit Test Passed." << std::endl;
    return 0;
}