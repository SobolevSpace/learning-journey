// 策略模式

#include <iostream>

class IStrategy{
public:
    virtual ~IStrategy() = default;
    virtual double CalPrice(double raw) = 0;
};

class NoDiscount : public IStrategy{
public:
    double CalPrice(double raw) override {
        return raw;
    }
};

class Discount : public IStrategy{
public:
    explicit Discount(double rate) : m_rate(rate) {}
    double CalPrice(double raw) override {
        return raw * m_rate;
    }
private:
    double m_rate = 1.0;
};

class FullReduction : public IStrategy{
public:
    FullReduction(double full, double reduction) : m_full(full), m_reduction(reduction) {}
    double CalPrice(double raw) override {
        if (raw >= m_full) {
            return raw - m_reduction;
        }
        return raw;
    }
private:
    double m_full = 0.0;
    double m_reduction = 0.0;
};

class ShoppingCart{
public:
    ShoppingCart(IStrategy* strategy) : m_strategy(strategy) {}
    ~ShoppingCart() {
        if (m_strategy) {
            delete m_strategy;
        }
    }
    void SetStrategy(IStrategy* strategy) {
        if (m_strategy) {
            delete m_strategy;
        }
        m_strategy = strategy;
    }
    double CalPrice(double raw) {
        return m_strategy->CalPrice(raw);
    }
private:
    IStrategy* m_strategy = nullptr;
};

int main() {
    ShoppingCart cart(new NoDiscount());
    bool ret = true;
    if (cart.CalPrice(100) != 100) {
        ret = false;
    }
    cart.SetStrategy(new Discount(0.8));
    if (cart.CalPrice(100) != 80) {
        ret = false;
    }
    cart.SetStrategy(new FullReduction(100, 10));
    if (cart.CalPrice(100) != 90) {
        ret = false;
    }
    if (ret) {
        std::cout << "Unit Test Passed." << std::endl;
    } else {
        std::cout << "Error: Strategy Failed." << std::endl;
    }
    return 0;
}