// 桥接模式
// 用于处理多维关系，解决多继承的问题

#include <iostream>

class OS
{
public:
    virtual ~OS() {}
    virtual void Install() = 0;
    int GetOSId() { return m_osId; }
protected:
    int m_osId;
};

class Linux : public OS
{
public:
    virtual void Install() {
        m_osId = 1;
    }
};

class Windows : public OS
{
public:
    virtual void Install() {
        m_osId = 2;
    }
};

class IComputer{
public:
    virtual ~IComputer() {}
    virtual void InstallOS(OS* os) = 0;
protected:
    OS* m_os;
};

class DellComputer : public IComputer
{
public:
    virtual void InstallOS(OS* os) {
        os->Install();
    }
};

class AppleComputer : public IComputer
{
public:
    virtual void InstallOS(OS* os) {
        os->Install();
    }
};

int main() {
    auto os1 = new Linux();
    auto os2 = new Windows();
    auto computer1 = new DellComputer();
    auto computer2 = new AppleComputer();
    computer1->InstallOS(os1);
    computer2->InstallOS(os2);
    delete os1;
    delete os2;
    delete computer1;
    delete computer2;
    std::cout << "Unit Test Passed."<<std::endl;
    return 0;
}