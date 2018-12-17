#pragma once
#include "GameData.h"

class Bullet 
{
public:
    Bullet() {
        mbExist = false;
    };
    ~Bullet() {};

    //根据当前坐标打印子弹
    void PrintBullet();
    //清除子弹
    void ClearBullet();
    //检测子弹碰撞
    void BulletHit();
    //子弹移动
    void BulletFly();
    //检测当前位置
    bool BulletCheak();

//数据
    int mX;
    int mY;
    bool mbMy;
    bool mbExist;
    int mnDirection;
    int mnInitial;
};



