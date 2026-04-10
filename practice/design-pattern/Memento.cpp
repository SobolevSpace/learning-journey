// 备忘录模式

#include <iostream>
#include <string>
#include <vector>

class Memento {
friend class Player;
public:
    Memento(int hp, int mp) : m_hp(hp), m_mp(mp) {}
private:
    int m_hp;
    int m_mp;
};

class Player {
public:
    Player(int hp, int mp) : m_hp(hp), m_mp(mp) {}
    void SetHP(int hp) { m_hp = hp; }
    void SetMP(int mp) { m_mp = mp; }
    int GetHP() { return m_hp; }
    int GetMP() { return m_mp; }
    Memento CreateMemento() {
        return std::move(Memento(m_hp, m_mp));
    }
    void RestoreMemento(const Memento& memento) {
        m_hp = memento.m_hp;
        m_mp = memento.m_mp;
    }
    void Attack() {
        m_mp -= 1;
    }
    void BeAttacked() {
        m_hp -= 1;
    }
private:
    int m_hp;
    int m_mp;
};

class Gameplay{
public:
    void Save(Player* player) {
        m_memento.push_back(player->CreateMemento());
    }
    Memento Load(int index) {
        if (index < m_memento.size()) {
            return m_memento[index];
        } else {
            return Memento(0, 0);
        }
    }
private:
    std::vector<Memento> m_memento;
};

int main() {
    Player player(100, 100);
    Gameplay gameplay;
    gameplay.Save(&player);
    player.Attack();
    player.BeAttacked();
    bool ret = true;
    if (player.GetHP() != 99 || player.GetMP() != 99) {
        ret = false;
    }
    player.RestoreMemento(gameplay.Load(0));
    if (player.GetHP() != 100 || player.GetMP() != 100) {
        ret = false;
    }
    if (ret)
    {
        std::cout<<"Unit Test Passed."<<std::endl;
    } else {
        std::cout<<"Error: Memento Failed."<<std::endl;
    }
    
    return 0;
}