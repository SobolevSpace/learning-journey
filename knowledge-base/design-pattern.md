# 设计模式

## 单例模式 (Singleton)

### 定义
确保一个类只有一个实例，并提供一个全局访问点。

### 实现方式（C++ 模板）

```cpp
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
    Singleton& operator=(const Singleton&) = delete;
};
```

### 关键点

1. **懒初始化**：实例在第一次调用 `GetInstance()` 时才创建
2. **线程安全**：C++11 及以上标准保证局部静态变量的初始化是线程安全的
3. **禁止复制**：通过删除拷贝构造函数和拷贝赋值运算符
4. **模板泛化**：可对任何类型提供单例支持

### 使用示例

```cpp
class TestType {
public:
    float x;
    int y;

    TestType(float _x = 0.0f, int _y = 0) : x(_x), y(_y) {}
};

int main() {
    auto& instance1 = Singleton<TestType>::GetInstance();
    auto& instance2 = Singleton<TestType>::GetInstance();
    // instance1 和 instance2 是同一个对象
}
```

### 待完善
- 带参构造类型的单例模式
