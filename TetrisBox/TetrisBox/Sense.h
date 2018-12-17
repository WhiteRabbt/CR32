#pragma once
#include "Tetris.h"
#include <Windows.h>
#define HEIGTH 24
#define WIDTH 12
#define BLOCK 1
#define WALL 2
#define SPACE 0

class Sense
{
public:
    Sense() = default;
    ~Sense();
public:
   
    //初始化场景
    void InitSense(Box &box);

    //游戏结束
    int GameIsOver();

    //显示游戏界面
    void ShowBg();

    //显示方块
    void ShowBox(const Box &box);

    //设置方块
    void SetBox(const Box &tBox);

    //下移
    void Down( Box &tBox);

    //判断是否可以移动
    int IsMove(int x, int y, const Box &tBox);

    //销毁方块
    void DestroyBox(const Box &tBox);

    //返回等级
    int RetLevel();

    //右移
    void Right(const Box &tBox);

    //左移
    void Lfet(const Box &tBox);

    //旋转
    void Rotate( Box &tBox);
 

    //消行
    void DestroyLine();

    //设置在控制台光标位置
    void MySetConsoleCursorPos(int x,int y);
private:
    //初始化边框
    void Init();

    //消行子函数
    void CopyArr(int index);
private:
    COORD cursorPos;
    int m_SenseX = 3;
    int m_SenseY = 0;
    static int sm_nScore ;
    static int sm_nLevel ;
    static int sm_Frame[HEIGTH][WIDTH];
};

