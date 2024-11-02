#include <gtest/gtest.h>
#include "dynamic_array.hpp"
#include "custom_mr.hpp"
#include <string>


TEST(DynamicArrayTest, IntPushBackAndAccess) {
    CustomMemoryResource memory_resource;
    DynamicArray<int> intArray(&memory_resource);

    intArray.push_back(10);
    intArray.push_back(20);
    intArray.push_back(30);

    EXPECT_EQ(intArray[2], 30);
}

TEST(DynamicArrayTest, IntPopBack) {
    CustomMemoryResource memory_resource;
    DynamicArray<int> intArray(&memory_resource);
    intArray.push_back(10);
    intArray.push_back(20);

    intArray.pop_back();

    EXPECT_EQ(intArray[0], 10);
}

struct MyStruct {
    int id;
    double value;
    std::string name;

    MyStruct(int i, double v, std::string n) : id(i), value(v), name(std::move(n)) {}

    bool operator==(const MyStruct& other) const {
        return id == other.id && value == other.value && name == other.name;
    }
};

TEST(DynamicArrayTest, StructPushBackAndAccess) {
    CustomMemoryResource memory_resource;
    DynamicArray<MyStruct> structArray(&memory_resource);

    MyStruct s1{1, 10.5, "First"};
    MyStruct s2{2, 20.75, "Second"};
    MyStruct s3{3, 30.25, "Third"};

    structArray.push_back(s1);
    structArray.push_back(s2);
    structArray.push_back(s3);

    EXPECT_EQ(structArray[0], s1);
    EXPECT_EQ(structArray[1], s2);
    EXPECT_EQ(structArray[2], s3);
}

TEST(DynamicArrayTest, IteratorFunctionality) {
    CustomMemoryResource memory_resource;
    DynamicArray<int> intArray(&memory_resource);
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);

    int sum = 0;

    for (auto it = intArray.begin(); it != intArray.end(); ++it) {
        sum += *it;
    }

    EXPECT_EQ(sum, 6);
}

TEST(CustomMemoryResourceTest, AllocateAndDeallocate) {
    CustomMemoryResource memory_resource;

    void* ptr1 = memory_resource.allocate(128, alignof(int));
    void* ptr2 = memory_resource.allocate(256, alignof(double));
    memory_resource.deallocate(ptr1, 128, alignof(int));
    void* ptr3 = memory_resource.allocate(128, alignof(int));

    EXPECT_EQ(ptr1, ptr3);
    memory_resource.deallocate(ptr2, 256, alignof(double));
    memory_resource.deallocate(ptr3, 128, alignof(int));
}

TEST(DynamicArrayTest, ClearMethod) {
    CustomMemoryResource memory_resource;
    DynamicArray<int> intArray(&memory_resource);
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);

    intArray.clear();

    EXPECT_EQ(intArray.size(), 0);
}

TEST(DynamicArrayTest, ReserveCapacity) {
    CustomMemoryResource memory_resource;
    DynamicArray<int> intArray(&memory_resource);

    intArray.push_back(1);
    intArray.push_back(2);

    EXPECT_GE(intArray.capacity(), intArray.size());
}

TEST(DynamicArrayTest, MoveElementsOnResize) {
    CustomMemoryResource memory_resource;
    DynamicArray<MyStruct> structArray(&memory_resource);

    structArray.push_back(MyStruct{1, 10.0, "A"});
    structArray.push_back(MyStruct{2, 20.0, "B"});

    structArray.push_back(MyStruct{3, 30.0, "C"});

    EXPECT_EQ(structArray[2].name, "C");
}

TEST(DynamicArrayTest, LargeNumberOfElements) {
    CustomMemoryResource memory_resource;
    DynamicArray<int> intArray(&memory_resource);
    const int numElements = 1000;

    for (int i = 0; i < numElements; ++i) {
        intArray.push_back(i);
    }

    EXPECT_EQ(intArray.size(), numElements);
}

