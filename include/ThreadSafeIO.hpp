#pragma once
#include <iostream>
#include <mutex>
#include <string>

class ThreadSafeIO {
    static std::mutex m;
public:
    static void printMap(char arr[101][101]);
    static void printMessage(const std::string&);
};