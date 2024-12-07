#include <gtest/gtest.h>

#include "executor.h"
class ExecutorTest : public ::testing::Test
{
protected:
    Executor car;  // 被测试的Executor
    void SetUp() override
    {
        car = Executor();  // 初始化
    }
};
// 初始化
TEST_F(ExecutorTest, Initialization)  // 在运行测试用例时将测试用例和ExecutorTest类关联
{
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 0);
    EXPECT_EQ(loc.first.second, 0);
    EXPECT_EQ(loc.second, 'N');
}
// 前进
TEST_F(ExecutorTest, MoveForward)
{
    car.DoCommand("M");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 0);   // x仍为0
    EXPECT_EQ(loc.first.second, 1);  // y增加到1
    EXPECT_EQ(loc.second, 'N');      // 方向仍然是N
}

// 左转
TEST_F(ExecutorTest, TurnLeft)
{
    car.DoCommand("L");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 0);   // x为0
    EXPECT_EQ(loc.first.second, 0);  // y为0
    EXPECT_EQ(loc.second, 'W');      // 方向变为W
}

// 右转
TEST_F(ExecutorTest, TurnRight)
{
    car.DoCommand("R");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 0);   // x为0
    EXPECT_EQ(loc.first.second, 0);  // y为0
    EXPECT_EQ(loc.second, 'E');      // 方向变为E
}

// 组合
TEST_F(ExecutorTest, CombinedCommands)
{
    car.DoCommand("MMM");
    car.DoCommand("L");
    car.DoCommand("M");
    car.DoCommand("R");
    car.DoCommand("M");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, -1);  // x为-1
    EXPECT_EQ(loc.first.second, 4);  // y为4
    EXPECT_EQ(loc.second, 'N');      // 方向为N
}
// 测试查询接口，顺便再测试一组组合指令
TEST_F(ExecutorTest, Query)
{
    car.DoCommand("MRMMLLLM");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 2);   // x为2
    EXPECT_EQ(loc.first.second, 0);  // y为0
    EXPECT_EQ(loc.second, 'S');      // 方向为S
}
TEST_F(ExecutorTest,Accelerate){
    car.DoCommand("F");  // 开始加速
    car.DoCommand("M");  // 加速状态下前进2格
    auto loc = car.GetInfo();
     EXPECT_EQ(loc.first.first, 0);   // x仍为0
    EXPECT_EQ(loc.first.second, 2);  // y为2
    EXPECT_EQ(loc.second, 'N');      // 方向仍然是N
}
// 倒车
TEST_F(ExecutorTest, Reverse)
{
    car.DoCommand("B");
    car.DoCommand("M");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 0);   // x仍为0
    EXPECT_EQ(loc.first.second, -1);  // y减少1
    EXPECT_EQ(loc.second, 'N');      // 方向仍然是N
}

// 加速状态下倒车
TEST_F(ExecutorTest, AccelerateAndReverse)
{
    car.DoCommand("F");
    car.DoCommand("B");
    car.DoCommand("M");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 0);   // x仍为0
    EXPECT_EQ(loc.first.second, -2);  // y减少2
    EXPECT_EQ(loc.second, 'N');      // 方向仍然是N
}

// 倒车后左转
TEST_F(ExecutorTest, ReverseAndTurnLeft)
{
    car.DoCommand("F");
    car.DoCommand("B");
    car.DoCommand("L");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 0);   // x仍为0
    EXPECT_EQ(loc.first.second, -1);  // y仍为0
    EXPECT_EQ(loc.second, 'E');      // 方向变为E
}

// 倒车后右转
TEST_F(ExecutorTest, ReverseAndTurnRight)
{
    car.DoCommand("F");
    car.DoCommand("B");
    car.DoCommand("R");
    auto loc = car.GetInfo();
    EXPECT_EQ(loc.first.first, 0);   // x仍为0
    EXPECT_EQ(loc.first.second, -1);  // y仍为0
    EXPECT_EQ(loc.second, 'W');      // 方向变为W
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}