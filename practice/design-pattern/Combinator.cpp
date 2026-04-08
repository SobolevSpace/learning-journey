// 组合模式

#include <iostream>
#include <string>
#include <vector>

class INode{
public:
    INode(const std::string& _name) : name(_name) {}
    virtual ~INode() {}
    virtual void Add(INode* node) {}
    virtual void Display(int depth) const = 0;
protected:
    std::string name;
};

class LeafNode : public INode{
public:
    LeafNode(const std::string& _name) : INode(_name) {}
    virtual void Display(int depth) const override {
        for (int i = 0; i < depth; ++i) {
            std::cout << "-";
        }
        std::cout << name << std::endl;
    }
};

class CompositeNode : public INode{
public:
    CompositeNode(const std::string& _name) : INode(_name) {}
    virtual void Add(INode* node) override {
        children.push_back(node);
    }
    virtual void Display(int depth) const override {
        for (int i = 0; i < depth; ++i) {
            std::cout << "-";
        }
        std::cout << name << std::endl;
        for (auto child : children) {
            child->Display(depth + 2);
        }
    }
private:
    std::vector<INode*> children;
};

int main() {
    CompositeNode* root = new CompositeNode("root");
    root->Add(new LeafNode("leaf1"));
    root->Add(new LeafNode("leaf2"));
    CompositeNode* node1 = new CompositeNode("node1");
    node1->Add(new LeafNode("leaf3"));
    node1->Add(new LeafNode("leaf4"));
    root->Add(node1);
    //root->Display(1);
    std::cout<<"Unit Test Passed."<<std::endl;
    return 0;
}