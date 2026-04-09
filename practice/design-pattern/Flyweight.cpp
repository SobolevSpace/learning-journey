// 享元模式

#include <iostream>
#include <map>
#include <string>

class TreeType{
private:
    std::string m_name;
public:
    TreeType(const std::string& name) : m_name(name) {}
};

class TreeTypeFactory{
private:
    std::map<std::string, TreeType*> m_treeTypes;
public:
    const TreeType* GetTreeType(const std::string& name) {
        if (m_treeTypes.find(name) == m_treeTypes.end()) {
            m_treeTypes[name] = new TreeType(name);
        }
        return m_treeTypes[name];
    }
};

class Tree{
private:
    const TreeType* m_treeType;
    int pos_x;
    int pos_y;
public:
    Tree(const TreeType* treeType, int x, int y) : m_treeType(treeType), pos_x(x), pos_y(y) {}
};

int main() {
    TreeTypeFactory factory;
    const TreeType* treeType = factory.GetTreeType("Oak");
    Tree tree(treeType, 1, 1);
    std::cout << "Unit Test Passed."<< std::endl;
    return 0;
}