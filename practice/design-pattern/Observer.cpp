// 观察者模式
// 这里有一个互相持有的指针 需要注意下

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void Update() = 0;
};

class ISubject {
public:
    virtual ~ISubject() {}
    virtual void Attach(IObserver* observer) {
        m_observers.insert(observer);
    };
    virtual void Detach(IObserver* observer) {
        m_observers.erase(observer);
    };
    virtual void Notify() {
        for (auto observer : m_observers) {
            observer->Update();
        }
    };
private:
    std::unordered_set<IObserver*> m_observers;
};

class Blog : public ISubject {
public:
    void WriteBlog(const std::string& blog) {
        m_blog = blog;
    }
    const std::string& GetBlog() {
        return m_blog;
    }

private:
    std::string m_blog;
};

class BlogObserver : public IObserver {
public:
    BlogObserver(Blog* blog) {
        m_blog = blog;
        m_blog->Attach(this);
    }
    void Update() override {
        std::cout << m_blog->GetBlog() << std::endl;
    }
private:
    Blog* m_blog;
};

int main() {
    Blog blog;
    BlogObserver observer1(&blog);
    BlogObserver observer2(&blog);
    blog.WriteBlog("Unit Test Passed.");
    blog.Notify();
    return 0;
}