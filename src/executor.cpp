#include "executor.h"
Executor::Executor(int initX, int initY, char initHeading) : x(initX), y(initY), heading(initHeading)
{
}
Executor::~Executor()
{
}
void Executor::DoCommand(const std::string& commands)
{
    for (auto command : commands) {
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
        }
    }
}
void Executor::Move()
{
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
void Executor::HeadLeft()
{
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
void Executor::HeadRight()
{
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
Location Executor::GetInfo()
{
    return {{x, y}, heading};
}