#include "executor.h"

Executor::Executor(int initX, int initY, char initHeading)
    : x(initX), y(initY), heading(initHeading), isAccelerating(false) {
    // 初始状态存储到历史栈中
    history.push({{x, y}, heading});
}

Executor::~Executor() {}

void Executor::DoCommand(const std::string& commands) {
    for (auto command : commands) {
        // 保存当前状态到历史栈中
        history.push({{x, y}, heading});
        
        switch (command) {
        case 'M':
            Move();
            break;
        case 'L':
            HeadLeft();
            break;
        case 'R':
            HeadRight();
            break;
        case 'F':
            ToggleAccelerating();
            break;
        }
    }
}

void Executor::Move() {
    if (isAccelerating) {
        // 加速状态下前进2格
        switch (heading) {
        case 'N':
            y += 2;
            break;
        case 'S':
            y -= 2;
            break;
        case 'E':
            x += 2;
            break;
        case 'W':
            x -= 2;
            break;
        }
    } else {
        // 普通状态下前进1格
        switch (heading) {
        case 'N':
            y++;
            break;
        case 'S':
            y--;
            break;
        case 'E':
            x++;
            break;
        case 'W':
            x--;
            break;
        }
    }
}

void Executor::HeadLeft() {
    if (isAccelerating) {
        // 加速状态下先前进1格，再左转
        switch (heading) {
        case 'N':
            y++;
            break;
        case 'S':
            y--;
            break;
        case 'E':
            x++;
            break;
        case 'W':
            x--;
            break;
        }
    }
    // 普通状态下左转
    switch (heading) {
    case 'N':
        heading = 'W';
        break;
    case 'S':
        heading = 'E';
        break;
    case 'E':
        heading = 'N';
        break;
    case 'W':
        heading = 'S';
        break;
    }
}

void Executor::HeadRight() {
    if (isAccelerating) {
        // 加速状态下先前进1格，再右转
        switch (heading) {
        case 'N':
            y++;
            break;
        case 'S':
            y--;
            break;
        case 'E':
            x++;
            break;
        case 'W':
            x--;
            break;
        }
    }
    // 普通状态下右转
    switch (heading) {
    case 'N':
        heading = 'E';
        break;
    case 'S':
        heading = 'W';
        break;
    case 'E':
        heading = 'S';
        break;
    case 'W':
        heading = 'N';
        break;
    }
}

Location Executor::GetInfo() {
    return {{x, y}, heading};
}

// 撤销操作：恢复到上一个状态
void Executor::Undo() {
    if (!history.empty()) {
        auto lastState = history.top();
        history.pop();
        x = lastState.first.first;
        y = lastState.first.second;
        heading = lastState.second;
    }
}

// 切换加速状态
void Executor::ToggleAccelerating() {
    isAccelerating = !isAccelerating;
}
