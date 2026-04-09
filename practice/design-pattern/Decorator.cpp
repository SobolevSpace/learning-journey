// 装饰器模式
// 核心思想是做接口的继承，保持原有对象的功能下增加新的功能

#include <iostream>
#include <string>
using namespace std;

class IComponent {
 public:
  virtual void operation() = 0;
};

class ConcreteComponent : public IComponent {
 public:
  void operation() { }
};

class Decorator : public IComponent {
 public:
  Decorator(IComponent* component) { this->component = component; }
  void operation() { component->operation(); }

 private:
  IComponent* component;
};

class ConcreteDecoratorA : public Decorator {
 public:
  ConcreteDecoratorA(IComponent* component) : Decorator(component) {}
  void operation() {
    Decorator::operation();
    addedBehavior();
  }
  void addedBehavior() { std::cout<<"Unit Test Passed."<<std::endl; }
};

class ConcreteDecoratorB : public Decorator {
 public:
  ConcreteDecoratorB(IComponent* component) : Decorator(component) {}
  void operation() {
    Decorator::operation();
    addedBehavior();
  }
  void addedBehavior() { }
};

int main() {
  IComponent* component = new ConcreteComponent();
  Decorator* decorator = new ConcreteDecoratorA(component);
  decorator->operation();

  return 0;
}