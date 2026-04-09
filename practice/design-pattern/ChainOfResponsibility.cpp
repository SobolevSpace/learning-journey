// 责任链模式

#include <iostream>
#include <vector>
using namespace std;

class IManager {
public:
    virtual int HandleAskForLeave(int days) = 0;
    void SetNext(IManager* manager) {
        m_next = manager;
    }
protected:
    IManager* m_next = nullptr;
};

class GroupLeader : public IManager {
public:
    int HandleAskForLeave(int days) override {
        if (days <= 3) {
            return days;
        } else {
            return m_next->HandleAskForLeave(days);
        }
    }
};

class Director : public IManager {
public:
    int HandleAskForLeave(int days) override {
        if (days <= 7) {
            return days;
        } else {
            return m_next->HandleAskForLeave(days);
        }
    }
};

class GeneralManager : public IManager {
public:
    int HandleAskForLeave(int days) override {
        if (days <= 30) {
            return days;
        } else {
            return 0;
        }
    }
};

int main() {
    auto groupLeader = new GroupLeader();
    auto director = new Director();
    auto generalManager = new GeneralManager();
    groupLeader->SetNext(director);
    director->SetNext(generalManager);
    std::vector<int> days = {1, 3, 5, 7, 10, 30, 31};
    std::vector<int> results = {1, 3, 5, 7, 10, 30, 0};
    bool ret = true;
    for (int i=0;i<days.size();i++) {
        if (groupLeader->HandleAskForLeave(days[i]) != results[i]) {
            ret = false;
            break;
        }
    }
    if (ret) {
        std::cout << "Unit Test Passed" << std::endl;
    } else {
        std::cout << "Error: ChainOfResponsibility failed" << std::endl;
    }
    delete groupLeader;
    delete director;
    delete generalManager;
    return 0;
}