// 状态模式

#include <iostream>

class Scheduler;

class IState{
public:
    virtual ~IState() = default;
    void SetScheduler(Scheduler* scheduler) { m_scheduler = scheduler; }
    virtual void Handle() = 0;
protected:
    Scheduler* m_scheduler;
};

class Scheduler{
public:
    Scheduler(IState* state): m_state(state) { m_state->SetScheduler(this); }
    ~Scheduler() { delete m_state; }
    void SetState(IState* state) { 
        if (m_state) {
            delete m_state;
        }
        m_state = state; 
        m_state->SetScheduler(this);
    }
    void Schedule() { m_state->Handle(); }
private:
    IState* m_state;
};

class ProcessTerminated : public IState{
public:
    void Handle() override {
        std::cout<< "Unit Test Passed." << std::endl;
    }
};

class ProcessRunning : public IState{
public:
    void Handle() override {
        //std::cout << "ProcessRunning" << std::endl;
        m_scheduler->SetState(new ProcessTerminated());
    }
};

class ProcessReady : public IState{
public:
    void Handle() override {
        //std::cout << "ProcessReady" << std::endl;
        m_scheduler->SetState(new ProcessRunning());
    }
};

class ProcessNew : public IState{
public:
    void Handle() override {
        //std::cout << "ProcessNew" << std::endl;
        m_scheduler->SetState(new ProcessReady());
    }
};

int main() {
    Scheduler scheduler(new ProcessNew());
    scheduler.Schedule();
    scheduler.Schedule();
    scheduler.Schedule();
    scheduler.Schedule();

    return 0;
}