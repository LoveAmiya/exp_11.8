#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <stack>

typedef std::pair<std::pair<int, int>, char> Location;

class Executor {
private:
    int x, y;       // 位置
    char heading;   // 朝向
    bool isAccelerating; // 是否加速状态
    bool isReversing; // 是否倒车状态
    std::stack<Location> history;  // 存储历史位置与方向

public:
    Executor(int initX = 0, int initY = 0, char initHeading = 'N');
    void DoCommand(const std::string& commands);
    void Move();
    void HeadLeft();
    void HeadRight();
    Location GetInfo();
    void Undo();  // 撤销操作
    ~Executor();
    void ToggleAccelerating(); // 切换加速状态
    void ToggleReversing(); // 切换倒车状态
};
