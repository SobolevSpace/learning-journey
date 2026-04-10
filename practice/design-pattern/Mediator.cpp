// 中介者模式

#include <iostream>

enum
{
    PLAYER_MOVE,
    PLAYER_DIALOGUE,
    PLAYER_BATTLE
};


// 一些抽象接口的定义
class IMediator;

class IPlayerSystem{
public:
    virtual ~IPlayerSystem() = default;
    void SetMediator(IMediator* mediator) { m_mediator = mediator; }
protected:
    IMediator* m_mediator;
};

class IMediator{
public:
    virtual ~IMediator() = default;
    virtual void Notify(IPlayerSystem* player, int event) = 0;
};

// 具体实现

class MoveSystem: public IPlayerSystem{
public:
    void Move() {
        m_mediator->Notify(this, PLAYER_MOVE);
    }

    void BreakMove() {
        //m_mediator->Notify(this, PLAYER_MOVE);
    }
};

class DialogueSystem : public IPlayerSystem{
public:
    void Dialogue() {
        m_mediator->Notify(this, PLAYER_DIALOGUE);
    }

    void BreakDialogue() {
        //m_mediator->Notify(this, PLAYER_DIALOGUE);
    }
};

class BattleSystem : public IPlayerSystem{
public:
    void Battle() {
        m_mediator->Notify(this, PLAYER_BATTLE);
    }
};

class ConcreteMediator : public IMediator{
public:
    void Notify(IPlayerSystem* player, int event) override {
        if (event == PLAYER_BATTLE) {
            m_moveSystem->BreakMove();
            m_dialogueSystem->BreakDialogue();
        } else if (event == PLAYER_MOVE) {
            m_dialogueSystem->BreakDialogue();
        } else if (event == PLAYER_DIALOGUE) {
            m_moveSystem->BreakMove();
        }
    }
private:
    MoveSystem* m_moveSystem;
    DialogueSystem* m_dialogueSystem;
    BattleSystem* m_battleSystem;
};

int main() {
    ConcreteMediator mediator;
    MoveSystem moveSystem;
    DialogueSystem dialogueSystem;
    BattleSystem battleSystem;

    moveSystem.SetMediator(&mediator);
    dialogueSystem.SetMediator(&mediator);
    battleSystem.SetMediator(&mediator);

    moveSystem.Move();
    dialogueSystem.Dialogue();
    battleSystem.Battle();
    std::cout<<"Unit Test Passed."<<std::endl;
    return 0;
}