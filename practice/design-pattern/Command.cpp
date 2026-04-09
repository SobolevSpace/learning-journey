// 命令模式

#include <iostream>
#include <list>
#include <string>

class Chef{
public:
    void cookDish1(){}

    void cookDish2(){}
};

class ICommand{
public:
    ICommand(Chef* chef):chef_(chef){}
    virtual void execute() = 0;
    virtual ~ICommand() = default;
protected:
    Chef* chef_;
};

class CookDish1Command : public ICommand{
public:
    CookDish1Command(Chef* chef):ICommand(chef){}
    void execute() override {
        chef_->cookDish1();
    }
};

class CookDish2Command : public ICommand{
public:
    CookDish2Command(Chef* chef):ICommand(chef){}
    void execute() override {
        chef_->cookDish2();
    }
};

class Waiter{
public:
    void AddCommand(ICommand* command){
        commands_.push_back(command);
    }

    void RemoveCommand(ICommand* command){
        commands_.remove(command);
    }
    
    void NotifyExecute(){
        for(auto command : commands_){
            command->execute();
        }
    }
private:
    std::list<ICommand*> commands_;
};


int main(){
    Chef* chef = new Chef();
    CookDish1Command* cookDish1Command = new CookDish1Command(chef);
    CookDish2Command* cookDish2Command = new CookDish2Command(chef);
    Waiter* waiter = new Waiter();
    waiter->AddCommand(cookDish1Command);
    waiter->AddCommand(cookDish2Command);
    waiter->NotifyExecute();
    std::cout<<"Unit Test Passed."<<std::endl;
    return 0;
}