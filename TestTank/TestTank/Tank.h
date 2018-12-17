#pragma once
#include "GameData.h"
#include "Bullet.h"

class Tank
{
public:
    Tank()
    {
        mX = 0;
        mY = 0;
        mbMyTank = false;
        mnDirection = DOWN;
        mbExist = 0;
        mnCD = 0;
        mnModel = 0;
        mnStop = 0;
        mnReviveCnt = 0;
    };
    ~Tank() {}
    //成员函数
    //根据地图检测坦克是否存在
    void CheckExist();
    //复活坦克
    virtual void ReveieTank();
    //检测出生位置
    int BirthPosCheck(int x, int y);
    //打印坦克(改变屏幕显示和数据)
    void PrintTank();
    //坦克碰撞检测(默认当前位置和方向)
    bool TankIsHit();
    //清除坦克(默认当前位置)(擦去屏幕和数据内容)
    void ClearTank();
    //坦克移动
    void Move();
    //生成子弹
    virtual void BuildBullet();
    virtual void CotrolTank();

    //数据成员
public:
    Bullet mBullet;         //子弹
    int mX;                 //坦克x坐标(数据)
    int mY;                 //坦克y坐标(数据)
    bool mbMyTank;          //坦克判别(我的为1否则为敌方坦克)
    int mnDirection;        //坦克方向
    bool mbExist;           //坦克是否存在
    int mnReviveCnt;        //坦克复活次数
    int mnCD;               //坦克发射子弹CD
    int mnModel;            //坦克模型
    int mnStop;             //坦克移动状态

};
//我方坦克类
class MyTank :public Tank
{
public:
    MyTank();
    ~MyTank();
    void ReveieTank()override;
    void BuildBullet()override;
    void CotrolTank();
};






