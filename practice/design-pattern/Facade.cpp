// 外观模式
// 核心思想是将多个子系统接口转换为一个统一的接口

#include <iostream>

class SubSystemA {
public:
    void OperationA(int& value) { value = 10; }
};

class SubSystemB {
public:
    void OperationB(int& value) { value++; }
};

class SubSystemC {
public:
    void OperationC(int& value) { value++; }
};

class Facade {
public:
    Facade() {
        m_subSystemA = new SubSystemA();
        m_subSystemB = new SubSystemB();
        m_subSystemC = new SubSystemC();
    }
    ~Facade() {
        delete m_subSystemA;
        delete m_subSystemB;
        delete m_subSystemC;
    }
    void Operation() {
        int testValue = 0;
        m_subSystemA->OperationA(testValue);
        m_subSystemB->OperationB(testValue);
        m_subSystemC->OperationC(testValue);
        if (testValue == 12) {
            std::cout << "Unit Test Passed." << std::endl;
        } else {
            std::cout<< "Error: Facade Failed."<<std::endl;
        }
    }

    private:
        SubSystemA* m_subSystemA;
        SubSystemB* m_subSystemB;
        SubSystemC* m_subSystemC;
};

int main() {
        Facade* facade = new Facade();
        facade->Operation();
        delete facade;
        return 0;
}