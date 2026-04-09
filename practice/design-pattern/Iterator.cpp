// 迭代器模式

#include <iostream>
#include <vector>
#include <string>

class Iterator{
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual void first() = 0;
    virtual int next() = 0;
    virtual std::string currentItem() const = 0;
};

class ConcreteIterator : public Iterator{
public:
    ConcreteIterator(std::vector<int> &data) : data_(data), index_(0) {}
    bool hasNext() const override {
        return index_ < data_.size();
    }
    void first() override {
        index_ = 0;
    }
    int next() override {
        return data_[index_++];
    }
    std::string currentItem() const override {
        return std::to_string(data_[index_]);
    }
private:
    std::vector<int> &data_;
    int index_;
};

class Aggregate{
public:
    virtual ~Aggregate() = default;
    virtual Iterator* createIterator() = 0;
};

class ConcreteAggregate : public Aggregate{
public:
    ConcreteAggregate(std::vector<int> data) : data_(data) {}
    Iterator* createIterator() override {
        return new ConcreteIterator(data_);
    }
private:
    std::vector<int> data_;
};

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    ConcreteAggregate aggregate(data);
    Iterator* iterator = aggregate.createIterator();
    std::vector<int> result;
    while (iterator->hasNext()) {
        result.push_back(iterator->next());
    }
    if (result == data) {
        std::cout << "Unit Test Pass." << std::endl;
    } else {
        std::cout << "Error: Iterator Failed." << std::endl;
    }
    delete iterator;
    return 0;
}