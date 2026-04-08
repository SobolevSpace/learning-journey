// 包含各种工厂的实现
// tips: 可以用dynamic_cast来判断指针实际类型

#include <iostream>
#include <cmath>
#include <map>

// 实现1， 简单工厂
// 分拣逻辑写在工厂类中，适用于创建少量对象的情况
class IOperator{
public:
    virtual float Operation(float lhs, float rhs) = 0;
    virtual ~IOperator() = default;
};

class AddOperator : public IOperator{
public:
    virtual float Operation(float lhs, float rhs) override {
        return lhs + rhs;
    }
};

class SubOperator : public IOperator{
public:
    virtual float Operation(float lhs, float rhs) override {
        return lhs - rhs;
    }
};

class OperatorFactory1{
public:
    static IOperator* CreateOperator(char op) {
        switch (op) {
            case '+':
                return new AddOperator();
            case '-':
                return new SubOperator();
            default:
                return nullptr;
        }
    }
};

// 实现1的单元测试
bool test1() {
    IOperator* op = OperatorFactory1::CreateOperator('+');
    bool ret = true;
    if (std::abs(op->Operation(1.0f, 1.0f) - 2.0f) > 0.00001f) {
        ret = false;
    }
    // judge type
    if (dynamic_cast<AddOperator*>(op) == nullptr) {
        ret = false;
    }
    IOperator* op2 = OperatorFactory1::CreateOperator('-');
    if (std::abs(op2->Operation(1.0f, 1.0f) - 0.0f) > 0.00001f) {
        ret = false;
    }
    if (dynamic_cast<SubOperator*>(op2) == nullptr) {
        ret = false;
    }
    return ret;
}

// 实现2， 工厂方法
// 分拣逻辑由类型天然完成，由工厂子类执行实例化操作
// 增加新类型不需要修改其他子类代码，更符合单一职责原则
class OperatorFactory2{
public:
    virtual IOperator* CreateOperator() = 0;
    virtual ~OperatorFactory2() = default;
};

class AddOperatorFactory2: public OperatorFactory2{
public:
    virtual IOperator* CreateOperator() override {
        return new AddOperator();
    }
};

class SubOperatorFactory2: public OperatorFactory2{
public:
    virtual IOperator* CreateOperator() override {
        return new SubOperator();
    }
};

bool test2() {
    OperatorFactory2* add_factory = new AddOperatorFactory2();
    IOperator* op = add_factory->CreateOperator();
    bool ret = true;
    if (std::abs(op->Operation(1.0f, 1.0f) - 2.0f) > 0.00001f) {
        ret = false;
    }
    // judge type
    if (dynamic_cast<AddOperator*>(op) == nullptr) {
        ret = false;
    }
    OperatorFactory2* sub_factory = new SubOperatorFactory2();
    IOperator* op2 = sub_factory->CreateOperator();
    if (std::abs(op2->Operation(1.0f, 1.0f) - 0.0f) > 0.00001f) {
        ret = false;
    }
    if (dynamic_cast<SubOperator*>(op2) == nullptr) {
        ret = false;
    }
    return ret;
}

// 实现3， 抽象工厂
// 用于创建一系列产品的情况 比较复杂
class IPhone {
public:
    virtual ~IPhone() = default;
};

class ApplePhone : public IPhone {
};

class HuaweiPhone : public IPhone {
};

class IMac{
public: 
    virtual ~IMac() = default;
};

class AppleMac : public IMac {
};

class HuaweiMac : public IMac {
};

class Factory3 {
public:
    virtual IPhone* CreatePhone() = 0;
    virtual IMac* CreateMac() = 0;
    virtual ~Factory3() = default;
};

class AppleProducer : public Factory3 {
public:
    virtual IPhone* CreatePhone() override {
        return new ApplePhone();
    }
    virtual IMac* CreateMac() override {
        return new AppleMac();
    }
};

class HuaweiProducer : public Factory3 {
public:
    virtual IPhone* CreatePhone() override {
        return new HuaweiPhone();
    }
    virtual IMac* CreateMac() override {
        return new HuaweiMac();
    }
};

bool test3() {
    Factory3* apple_factory = new AppleProducer();
    IPhone* phone = apple_factory->CreatePhone();
    IMac* mac = apple_factory->CreateMac();
    if (dynamic_cast<ApplePhone*>(phone) == nullptr) {
        return false;
    }
    if (dynamic_cast<AppleMac*>(mac) == nullptr) {
        return false;
    }
    Factory3* huawei_factory = new HuaweiProducer();
    IPhone* phone2 = huawei_factory->CreatePhone();
    IMac* mac2 = huawei_factory->CreateMac();
    if (dynamic_cast<HuaweiPhone*>(phone2) == nullptr) {
        return false;
    }
    if (dynamic_cast<HuaweiMac*>(mac2) == nullptr) {
        return false;
    }
    return true;
}



// 实现4， 带模板，增加类型基本不需要修改其他代码
template <typename AbstractProduct_t>
class AbstractFactory {
public:
    virtual AbstractProduct_t* CreateProduct() = 0;
    virtual ~AbstractFactory() = default;
};

template <typename AbstractProduct_t, typename ConcreteProduct_t>
class ConcreteFactory : public AbstractFactory<AbstractProduct_t> {
public:
    virtual AbstractProduct_t* CreateProduct() override {
        return new ConcreteProduct_t();
    }
};

// 实现4的单元测试
bool test4() {
    ConcreteFactory<IOperator, AddOperator> add_factory;
    IOperator* op = add_factory.CreateProduct();
    bool ret = true;
    if (std::abs(op->Operation(1.0f, 1.0f) - 2.0f) > 0.00001f) {
        ret = false;
    }
    // judge type
    if (dynamic_cast<AddOperator*>(op) == nullptr) {
        ret = false;
    }
    ConcreteFactory<IOperator, SubOperator> sub_factory;
    IOperator* op2 = sub_factory.CreateProduct();
    if (std::abs(op2->Operation(1.0f, 1.0f) - 0.0f) > 0.00001f) {
        ret = false;
    }
    if (dynamic_cast<SubOperator*>(op2) == nullptr) {
        ret = false;
    }
    return ret;
}

// 实现5, 增删类型最便捷，利用模板特性，而且是单例（对抽象类），可以管理一类产品的所有构造
// 有一定开销，需要查找std::map
// 需要防止重复注册之类的事情
template <typename Product_t>
class IProductRegistry {
public:
    virtual Product_t* CreateProduct() = 0;
protected:
// 禁止外部构造和析构， 子类内部可以用
    IProductRegistry() = default;
    virtual ~IProductRegistry() = default;
private:
// 禁止拷贝和赋值
    IProductRegistry(const IProductRegistry&) = delete;
    IProductRegistry& operator=(const IProductRegistry&) = delete;
};

template <class Product_t>
class ProductFactory{
public:
// 单例模式
    static ProductFactory<Product_t> &GetInstance() {
        static ProductFactory<Product_t> instance;
        return instance;
    }

    void RegisterProduct(IProductRegistry<Product_t>* product, const std::string& name) {
        m_productRegistry[name] = product;
    }

    Product_t* CreateProduct(const std::string& name) {
        if (m_productRegistry.find(name) == m_productRegistry.end()) {
            return nullptr;
        }
        return m_productRegistry[name]->CreateProduct();
    }

private:
    std::map<std::string, IProductRegistry<Product_t>*> m_productRegistry;

// 禁止外部构造和析构
    ProductFactory() = default;
    ~ProductFactory() = default;
    ProductFactory(const ProductFactory&) = delete;
    const ProductFactory& operator=(const ProductFactory&) = delete;
};

template <typename ProductType_t, typename ProductImpl_t>
class ProductRegistry : public IProductRegistry<ProductType_t> {
public:
    virtual ProductType_t* CreateProduct() override {
        return new ProductImpl_t();
    }

    explicit ProductRegistry(const std::string& name) {
        ProductFactory<ProductType_t>::GetInstance().RegisterProduct(this, name);
    }
};

bool test5() {
    bool ret = true;
    const std::string ADD = "add";
    const std::string SUB = "sub";
    ProductRegistry<IOperator, AddOperator> add_registry(ADD);
    ProductRegistry<IOperator, SubOperator> sub_registry(SUB);
    IOperator* op = ProductFactory<IOperator>::GetInstance().CreateProduct(ADD);
    if (std::abs(op->Operation(1.0f, 1.0f) - 2.0f) > 0.00001f) {
        ret = false;
    }
    // judge type
    if (dynamic_cast<AddOperator*>(op) == nullptr) {
        ret = false;
    }
    IOperator* op2 = ProductFactory<IOperator>::GetInstance().CreateProduct(SUB);
    if (std::abs(op2->Operation(1.0f, 1.0f) - 0.0f) > 0.00001f) {
        ret = false;
    }
    if (dynamic_cast<SubOperator*>(op2) == nullptr) {
        ret = false;
    }
    return ret;
}

int main() {
    if (test1() && test2() && test3() && test4() && test5()) {
        std::cout<<"Unit Test Passed."<<std::endl;
    } else {
        std::cout<<"Error: Not SimpleFactory"<<std::endl;
    }
    return 0;
}