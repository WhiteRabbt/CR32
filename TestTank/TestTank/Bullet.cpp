#include "Bullet.h"
#include <stdio.h>
#include <Windows.h>

void Bullet::PrintBullet()
{
    GoToxy(mX * 2, mY);
    printf("●");
}

void Bullet::ClearBullet()
{
    GoToxy(mX * 2, mY);
    printf("  ");
}




void Bullet::BulletHit()
{
    //子弹碰到砖头
    if (g_arrMap[mY][mX] == WALL)
    {
        if (mnDirection == UP || mnDirection == DOWN)
        {
            for (int i = 0; i < 3; i++)
            {
                if (g_arrMap[mY][mX + i - 1] == WALL)
                {
                    g_arrMap[mY][mX + i - 1] = LAND;
                    GoToxy((mX + i - 1) * 2, mY);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    printf("  ");
                }
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                if (g_arrMap[mY + i - 1][mX] == WALL)
                {
                    g_arrMap[mY + i - 1][mX] = LAND;
                    GoToxy((mX) * 2, mY + i - 1);
                    printf("  ");
                }
            }
        }
        mbExist = false;
    }
    //子弹碰到边框或铁
    else if (g_arrMap[mY][mX] == FRAME || g_arrMap[mY][mX] == IRON)
    {
        mbExist = false;
    }
    //我的子弹碰到坦克
   else if (mbMy && (g_arrMap[mY][mX] == ENEMY_TANK))
    {
        mbExist = false;
        g_arrMap[mY][mX] = LAND;
    }
    //如果敌方子弹碰到我方坦克
    else if (g_arrMap[mY][mX] == MY_TANK && !mbMy)
    {
        mbExist = false;
        g_arrMap[mY][mX] = LAND;
    }
    else if (g_arrMap[mY][mX] == 9)
    {
        mbExist = false;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
        GoToxy(38, 37);	 printf("      ");
        GoToxy(38, 38);	 printf("◢◣  ");
        GoToxy(38, 39);	 printf("███");
        GoToxy(40, 20);
        printf("游戏结束");
        while (1)
        {
        }
    }
}

//碰撞返回真,否则假
bool Bullet::BulletCheak()
{
    if (g_arrMap[mY][mX] == LAND)
    {
        return false;
    }
    return true;
}

void Bullet::BulletFly()
{
    if (mbExist)
    {
        if (mnInitial == 0)
        {
            if (BulletCheak() == 0)
            {
                ClearBullet();
            }
            switch (mnDirection)
            {
            case UP:
                mY--;
                break;
            case DOWN:
                mY++;
                break;
            case LEFT:
                mX--;
                break;
            case RIGHT:
                mX++;
                break;
            }
        }
        if (BulletCheak() == 0)
        {
            PrintBullet();
        }
        else
        {
            BulletHit();
        }
        if (mnInitial)
        {
            mnInitial = 0;
        }
    }
}
