// 建造者模式

#include <iostream>

class IBuilder{
public:
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual void BuildPartC() = 0;

    virtual ~IBuilder() = default;

    bool StateCheck(int a, int b, int c) {
        return m_partA == a && m_partB == b && m_partC == c;
    }
protected:
    int m_partA;
    int m_partB;
    int m_partC;
};

class Builder1 : public IBuilder{
public:
    virtual void BuildPartA() {
        m_partA = 1;
    }
    virtual void BuildPartB() {
        m_partB = 1;
    }
    virtual void BuildPartC() {
        m_partC = 1;
    }

};

class Builder2 : public IBuilder{
public:
    virtual void BuildPartA() {
        m_partA = 2;
    }
    virtual void BuildPartB() {
        m_partB = 2;   
    }    
    virtual void BuildPartC() {
        m_partC = 2;
    }
};

class Director{
public:
    Director(IBuilder* builder) : builder_(builder) {}
    void Construct() {
        builder_->BuildPartA();
        builder_->BuildPartB();
        builder_->BuildPartC();
    }
private:
    IBuilder* builder_;
};

int main() {
    Builder1 builder1;
    Director director1(&builder1);
    director1.Construct();
    Builder2 builder2;
    Director director2(&builder2);
    director2.Construct();
    if (builder1.StateCheck(1, 1, 1) && builder2.StateCheck(2, 2, 2)) {
        std::cout << "Unit Test Passed." << std::endl;
    } else {
        std::cout << "Error: Builder Failed." << std::endl;
   }
   return 0;
}