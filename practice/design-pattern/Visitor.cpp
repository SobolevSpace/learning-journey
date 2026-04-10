// 访问者模式

#include <iostream>
#include <string>

// 发票
class Invoise;
// 报销单
class Expense;

class IVisitor{
public:
    virtual ~IVisitor() = default;
    virtual void Visit(Invoise* invoise) = 0;
    virtual void Visit(Expense* expense) = 0;
};

class IDocument{
public:
    virtual ~IDocument() = default;
    virtual void Accept(IVisitor& visitor) = 0;
};

class Invoise : public IDocument{
public:
    Invoise(double amount) : m_amount(amount) {}
    void Accept(IVisitor& visitor) override {
        visitor.Visit(this);
    }
    double GetAmount() const {
        return m_amount;
    }
private:
    double m_amount;
};

class Expense : public IDocument{
public:
    Expense(double amount, const std::string& category) : m_amount(amount), m_category(category) {}
    void Accept(IVisitor& visitor) override {
        visitor.Visit(this);
    }
    double GetAmount() const {
        return m_amount;
    }
    std::string GetCategory() const {
        return m_category;
    }
private:
    double m_amount;
    std::string m_category;
};

class TaxVisitor : public IVisitor{
public:
    void Visit(Invoise* invoise) override {
        m_tax += invoise->GetAmount() * 0.13;
    }
    void Visit(Expense* expense) override {
        m_tax += expense->GetAmount() * 0.03;
    }
    TaxVisitor() : m_tax(0.0) {}
    double GetTax() const {
        return m_tax;
    }
private:
    double m_tax;
};

int main() {
    TaxVisitor visitor;
    Invoise invoise(100.0);
    Expense expense(100.0, "Food");
    invoise.Accept(visitor);
    expense.Accept(visitor);
    if (visitor.GetTax() == 16.0) {
        std::cout<<"Unit Test Passed."<<std::endl;
    } else {
        std::cout<<"Error: Visitor Failed."<<std::endl;
    }
    return 0;
}