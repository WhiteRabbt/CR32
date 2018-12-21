#pragma once
#include "Const.h"
#include "Snack.h"
#include <Windows.h>
#define CHAR_WHIDTH 2

class Sence
{
public:
    Sence();
    ~Sence();

    //GameLogic
    void GameLogic();

    //接受键盘
    void Keyboard();
private:
    //初始化地图数据
    void InitData();

    //移动光标
    void MoveCursor(int x, int y);

    //打印游戏界面
    void PrintInterface();

    //打印头部
    void PrintHead();

    //打印尾部
    void  PrintTall(const char* psz = "  ");

    //打印食物
    void PrintFood();

   

private:
    Snack m_snack;

};

