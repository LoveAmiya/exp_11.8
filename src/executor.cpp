#include "executor.h"

// 构造函数，初始化Executor对象
Executor::Executor(int initX, int initY, char initHeading)
    : x(initX), y(initY), heading(initHeading), isAccelerating(false),isReversing(false),isSportsCar(false),isBus(false) {
    // 初始状态存储到历史栈中
    history.push({{x, y}, heading});
}

// 析构函数，释放Executor对象
Executor::~Executor() {}

// 执行命令
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
        case 'B':
            ToggleReversing();
            break;
        case 'S':
            ToggleSportsCar();
            break;
        case 'U':
            ToggleBus();
            break;
        }
    }
}

// 前进或者后退
void Executor::Move() {
    if(isSportsCar){
        // 跑车前进2格
        switch (heading) {
        case 'N':
            y+=2;
            break;
        case 'S':
            y-=2;
            break;
        case 'E':
            x+=2;
            break;
        case 'W':
            x-=2;
            break;
    }
    }
    if (isAccelerating && isReversing && !isSportsCar) {
        // 加速状态下后退2格
        switch (heading) {
        case 'N':
            y -= 2;
            break;
        case 'S':
            y += 2;
            break;
        case 'E':
            x -= 2;
            break;
        case 'W':
            x += 2;
            break;
        }
    } else if(isReversing && !isAccelerating && !isSportsCar) {
        // 普通状态下后退 1格
        switch (heading) {
        case 'N':
            y--;
            break;
        case 'S':
            y++;
            break;
        case 'E':
            x--;
            break;
        case 'W':
            x++;
            break;
        }
    }else if(isAccelerating && !isReversing && !isSportsCar) {
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
    }else if(!isAccelerating && !isReversing && !isSportsCar) {
        switch(heading){
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

// 左转
void Executor::HeadLeft() {
    if(isSportsCar){
        switch (heading) {
        case 'N':
            x--;
            heading = 'W';
            break;
        case 'S':
            x++;
            heading = 'E';
            break;
        case 'E':
            y++;
            heading = 'N';
            break;
        case 'W':
            y--;
            heading = 'S';
            break;
    }
    }
    if(isBus){
        switch (heading) {
        case 'N':
            y++;
            heading = 'W';
            break;
        case 'S':
            y--;
            heading = 'E';
            break;
        case 'E':
            x++;
            heading = 'N';
            break;
        case 'W':
            x--;
            heading = 'S';
            break;
    }
    }
    if (isAccelerating && isReversing && !isSportsCar && !isBus) {
        // 加速状态下先后退1格，再右转
        switch (heading) {
        case 'N':
            y--;
            heading = 'E';
            break;
        case 'S':
            y++;
            heading = 'W';
            break;
        case 'E':
            x--;
            heading = 'S';
            break;
        case 'W':
            x++;
            heading = 'N';
            break;
        }
    }else if(isReversing && !isAccelerating && !isSportsCar && !isBus) {
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
    }else if(isAccelerating && !isReversing && !isSportsCar && !isBus) {
        // 加速状态下先前进一格
        switch (heading) {
        case 'N':
            y++;
            heading = 'W';
            break;
        case 'S':
            y--;
            heading = 'E';
            break;
        case 'E':
            x++;
            heading = 'N';
            break;
        case 'W':
            x--;
            heading = 'S';
            break;
        }
    }else if(!isReversing && !isAccelerating && !isSportsCar && !isBus) {
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
}

// 右转
void Executor::HeadRight() {
    if(isSportsCar){
        switch (heading) {
        case 'N':
            x++;
            heading = 'E';
            break;
        case 'S':
            x--;
            heading = 'W';
            break;
        case 'E':
            y--;
            heading = 'S';
            break;
        case 'W':
            y++;
            heading = 'N';
            break;
    }
    }
    if(isBus){
        switch (heading) {
        case 'N':
            y++;
            heading = 'E';
            break;
        case 'S':
            y--;
            heading = 'W';
            break;
        case 'E':
            x++;
            heading = 'S';
            break;
        case 'W':
            x--;
            heading = 'N';
            break;
    }
    }
    if (isAccelerating && isReversing && !isSportsCar && !isBus) {
        // 加速状态下先后退1格，再左转
        switch (heading) {
        case 'N':
            y--;
            heading = 'W';
            break;
        case 'S':
            y++;
            heading = 'E';
            break;
        case 'E':
            x--;
            heading = 'N';
            break;
        case 'W':
            x++;
            heading = 'S';
            break;
        }
    }else if(isReversing && !isAccelerating && !isSportsCar && !isBus) {
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
    }else if(isAccelerating && !isReversing && !isSportsCar && !isBus) {
        // 加速状态下先前进1格，再右转
        switch (heading) {
        case 'N':
            y++;
            heading = 'E';
            break;
        case 'S':
            y--;
            heading = 'W';
            break;
        case 'E':
            x++;
            heading = 'S';
            break;
        case 'W':
            x--;
            heading = 'N';
            break;
        }
    }else if(!isReversing && !isAccelerating && !isSportsCar && !isBus) {
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
}

// 获取当前位置和朝向
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
void Executor::ToggleReversing(){
    isReversing = !isReversing;
}
void Executor::ToggleSportsCar() {
    isSportsCar = !isSportsCar;
}
void Executor::ToggleBus() {
    isBus = !isBus;
}