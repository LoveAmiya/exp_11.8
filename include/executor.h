#pragma once
#include <iostream>
#include <string>
#include <utility>
typedef std::pair<std::pair<int, int>, char> Location;
class Executor
{
private:
    int x, y;      // 位置
    char heading;  // 朝向
public:
    Executor(int initX = 0, int initY = 0, char initHeading = 'N');
    void DoCommand(const std::string& commands);
    void Move();
    void HeadLeft();
    void HeadRight();
    Location GetInfo();
    ~Executor();
};