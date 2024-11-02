#include <iostream>
#include <memory_resource>
#include "dynamic_array.hpp"
#include "custom_mr.hpp"

struct MyStruct {
    int id;
    double value;
    std::string name;

    MyStruct(int i, double v, std::string n) : id(i), value(v), name(std::move(n)) {}

    friend std::ostream& operator<<(std::ostream& os, const MyStruct& ms) {
        os << "ID: " << ms.id << ", Value: " << ms.value << ", Name: " << ms.name;
        return os;
    }
};

int main() {
    CustomMemoryResource memory_resource;

    DynamicArray<int> intArray{&memory_resource};
    intArray.push_back(10);
    intArray.push_back(20);
    intArray.push_back(30);

    std::cout << "DynamicArray<int> contents:" << std::endl;
    for (const auto& elem : intArray) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    DynamicArray<MyStruct> structArray{&memory_resource};
    structArray.push_back(MyStruct{1, 10.5, "First"});
    structArray.push_back(MyStruct{2, 20.75, "Second"});
    structArray.push_back(MyStruct{3, 30.25, "Third"});

    std::cout << "\nDynamicArray<MyStruct> contents:" << std::endl;
    for (const auto& elem : structArray) {
        std::cout << elem << std::endl;
    }

    return 0;
}
