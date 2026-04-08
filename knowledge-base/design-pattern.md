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

---

## 工厂模式 (Factory)

### 核心问题
对象创建的复杂性

### 主要解决的问题

1. **解耦对象创建和使用** - 客户端不需要知道具体类，只需通过工厂接口获取对象
   - 避免代码中出现大量 `new ConcreteClass()`

2. **封装创建逻辑** - 将复杂的初始化过程集中管理
   - 比如创建对象后还需要配置、依赖注入等步骤

3. **灵活扩展** - 新增产品类时，只需修改工厂或增加新工厂，无需修改客户端代码

4. **管理对象生命周期** - 工厂可以控制对象的创建、缓存、销毁

### 三种工厂模式对比

| 模式 | 工厂数量 | 适用场景 |
|------|----------|----------|
| 简单工厂 | 1个 | 产品类型少且固定 |
| 工厂方法 | 每个产品1个工厂 | 产品类型需要频繁扩展 |
| 抽象工厂 | 每个产品族1个工厂 | 多个相关产品需要一起创建 |

### 简单总结
把"怎么造"和"怎么用"分开
