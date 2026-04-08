// 适配器模式
// 一个例子是把deque适配成stack

#include <iostream>
#include <stack>
#include <deque>

template<typename T>
class Stack {
public:
    void push(const T& element) {
        container.push_back(element);
    }

    void pop() {
        container.pop_back();
    }

    T top() const {
        return container.back();
    }

    bool empty() const {
        return container.empty();
    }

    size_t size() const {
        return container.size();
    }

private:
    std::deque<T> container;
};

int main() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    bool ret = true;
    if (stack.top() != 3 || stack.size() != 3) {
        ret = false;
    }
    stack.pop();
    if (stack.top() != 2 || stack.size() != 2) {
        ret = false;
    }
    stack.pop();
    if (stack.top() != 1 || stack.size() != 1) {
        ret = false;
    }
    stack.pop();
    if (!stack.empty()) {
        ret = false;
    } 
    if (!ret) {
        std::cout << "Error: Adapter Failed." << std::endl;
    } else {
        std::cout << "Unit Test Passed." << std::endl;
    }

    return 0;
}