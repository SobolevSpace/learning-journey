// 模板方法模式

#include <iostream>
#include <string>

class ITestPaper{
public:
    virtual ~ITestPaper() = default;
    void Question1() {};
    void Question2() {};
    void Question3() {};
    void Test() {
        Question1();
        Answer1();
        Question2();
        Answer2();
        Question3();
        Answer3();
    }
protected:
    virtual void Answer1() = 0;
    virtual void Answer2() = 0;
    virtual void Answer3() = 0;
};

class TestPaperA : public ITestPaper {
private:
    void Answer1() override {
    }
    void Answer2() override {
        std::cout<<"Passed." << std::endl;
    }
    void Answer3() override {
    }
};

class TestPaperB : public ITestPaper {
private:
    void Answer1() override {
        std::cout<<"Unit ";
    }
    void Answer2() override {
    }
    void Answer3() override {
        std::cout<<"Test ";
    }
};


int main() {
    TestPaperB b;
    b.Test();
    TestPaperA a;
    a.Test();
    return 0;
}
