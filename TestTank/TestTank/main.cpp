// TestTank.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include "Tank.h"
#include "Bullet.h"
#include "GameData.h"

int main()
{
    int arrInterval[12] = { 0 };
   
    InitMap();
    MyTank myTank;
    Tank  arrTank[4];
    Tank *pTank[5] = { &arrTank[0],&arrTank[1],&arrTank[2],&arrTank[3],&myTank };
   
    
    while (1)
    {
        if (arrInterval[0]++ % SPPED == 0)
        {
            //子弹移动
            for (int i = 0; i < 5; i++)
            {
                pTank[i]->mBullet.BulletFly();
            }
            //检测坦克状态
            for (int i = 0; i < 5; i++)
            {
                pTank[i]->CheckExist();
            }
           // 坦克移动
            for (int i = 0; i < 4; i++)
            {
                if (arrInterval[i + 1]++ % 3 == 0)
                {
                    pTank[i]->Move();
                }
            }
            //坦克复活
            if (arrInterval[5]++ % 90 == 0)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (pTank[i]->mbExist == false && pTank[i]->mnReviveCnt < 4)
                    {
                        pTank[i]->ReveieTank();
                        break;
                    }
                }
            }
            //发射子弹
            for (int i = 0; i < 4; i++)
            {
                pTank[i]->BuildBullet();
            }
            //控制主坦克
            if (arrInterval[6]++ % 2 == 0)
            {
                pTank[4]->CotrolTank();
            }
        }
        Sleep(5);
    }
    std::cout << "Hello World!\n";
}








