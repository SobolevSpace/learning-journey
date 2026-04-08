// 原型模式

#include <iostream>

class IPrototype {
public:
    IPrototype() = default;
    IPrototype(const IPrototype& prototype) = default;
    virtual IPrototype* Clone() const {
        return new IPrototype(*this);
    }
    virtual ~IPrototype() = default;
};

class ConcretePrototype : public IPrototype {
public:
    ConcretePrototype() {
        m_size = 10;
        m_data = new int[m_size];
        for (int i = 0; i < m_size; i++) {
            m_data[i] = i;
        }
    }

    ConcretePrototype(const ConcretePrototype& prototype): IPrototype(prototype) {
        m_size = prototype.m_size;
        m_data = new int[m_size];
        for (int i = 0; i < m_size; i++) {
            m_data[i] = prototype.m_data[i];
        }
    };

    virtual IPrototype* Clone() const override{
        return new ConcretePrototype(*this);
    }

    virtual ~ConcretePrototype() {
        delete[] m_data;
    };

    bool operator==(const ConcretePrototype& prototype) const {
        if (m_size != prototype.m_size) {
            return false;
        }
        for (int i = 0; i < m_size; i++) {
            if (m_data[i] != prototype.m_data[i]) {
                return false;
            }
        }
        return true;
    }

private:
    int m_size = 0;
    int* m_data = nullptr;
};

int main() {
    ConcretePrototype prototype;
    IPrototype* clone = prototype.Clone();
    if (prototype == *dynamic_cast<ConcretePrototype*>(clone) && clone != &prototype) {
        std::cout << "Unit Test Passed." << std::endl;
    } else {
        std::cout << "Error: Not Prototype." << std::endl;
    }
    delete clone;
    return 0;
}