#pragma once
#include "Const.h"
#include <Windows.h>
#include <deque>

using namespace std;
class Snack
{
public:
    Snack();
    ~Snack();
    //设置方向
    void SetDir(int nDir);

    //根据方向插入一个首元素
    void InsertToBegin();

    //删除最后一个元素
    void DelEndElment();

    //得到首元素
    COORD GetBeginElment();

    //得到尾元素
    COORD GetEndElment();

    //检测碰撞
    bool HitCheak();

    //吃到食物检测
    bool EatFoodCheak();

    //生成食物
    void MakeFood();

    //得到食物坐标
    COORD GetFoodCoord();
private:

    //根据修改地图数据
    void ModifyMap(COORD coord, int nVal);

private:
    deque<COORD> m_vCoord;
    int m_Dir;
    short m_foodX;
    short m_foodY;
};

