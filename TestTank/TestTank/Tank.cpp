#include "Tank.h"
#include <stdlib.h>
#include <iostream>
#include <Windows.h>


void Tank::CheckExist()
{
    bool bExist = true;

    if (mbExist == true)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (g_arrMap[mY + i - 1][mX + j - 1] == LAND)
                {
                    bExist = false;
                    goto END;
                }
            }
        }
    }
END:
    if (bExist == false)
    {
        ClearTank();
        mbExist = false;
    }
}

void Tank::ReveieTank()
{
    int nRandVal = rand() % 3 - 1;

    mX = 20 + 18 * nRandVal;
    mY = 2;
    if (BirthPosCheck(mX, mY))
    {
        mbExist = true;
        mnStop = 0;
        mnDirection = DOWN;
        mnModel = 1;
        mnCD = 15;
        mnReviveCnt++;
        PrintTank();
    }
}
int Tank::BirthPosCheck(int x, int y)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (g_arrMap[y - 1 + i][x - 1 + j] != LAND)
            {
                return 0;
            }
        }
    }
    return 1;
}

void Tank::PrintTank()
{
    //通过模型选择坦克
    const char* (*szTempModel)[4] = g_TankModel[mnModel];
    for (int i = 0; i < 3; i++)
    {
        GoToxy((mX - 1) * 2, mY - 1 + i);
        printf("%s", szTempModel[i][mnDirection]);
        for (int j = 0; j < 3; j++)
        {
            if (mbMyTank)
            {
                g_arrMap[mY + i - 1][mX + j - 1] = MY_TANK;
            }
            else
            {
                g_arrMap[mY + i - 1][mX + j - 1] = ENEMY_TANK;
            }
        }
    }
}

bool Tank::TankIsHit()
{
    bool bRetVal = true;
    switch (mnDirection)
    {
    case UP:
        if (g_arrMap[mY - 2][mX - 1] == LAND && g_arrMap[mY - 2][mX] == LAND && g_arrMap[mY - 2][mX + 1] == LAND)
        {
            bRetVal = false;
        }
        break;
    case DOWN:
        if (g_arrMap[mY + 2][mX - 1] == LAND && g_arrMap[mY + 2][mX] == LAND && g_arrMap[mY + 2][mX + 1] == LAND)
        {
            bRetVal = false;
        }
        break;
    case LEFT:
        if (g_arrMap[mY - 1][mX - 2] == LAND && g_arrMap[mY][mX - 2] == LAND && g_arrMap[mY + 1][mX - 2] == LAND)
        {
            bRetVal = false;
        }
        break;
    case RIGHT:
        if (g_arrMap[mY - 1][mX + 2] == LAND && g_arrMap[mY][mX + 2] == LAND && g_arrMap[mY + 1][mX + 2] == LAND)
        {
            bRetVal = false;
        }
        break;
    }
    return bRetVal;
}

void Tank::ClearTank()
{
    for (int i = 0; i < 3; i++)
    {
        GoToxy((mX - 1) * 2, mY + i - 1);
        printf("      ");
        for (int j = 0; j < 3; j++)
        {
            g_arrMap[mY + i - 1][mX + j - 1] = LAND;
        }
    }
}

void Tank::Move()
{
    if (mbExist)
    {
        if (mnStop != 0)
        {
            mnStop--;
            return;
        }
        if (!(rand() % 10))
        {
            mnDirection = rand() % 4;
            if (rand() % 2)
            {
                mnStop = 3;
                return;
            }
        }
        ClearTank();
        if (!TankIsHit())
        {
            switch (mnDirection)
            {
            case UP:
                mY--;
                break;  //上前进一格
            case DOWN:
                mY++;
                break;  //下前进一格
            case LEFT:
                mX--;
                break;  //左前进一格
            case RIGHT:
                mX++;
                break;  //右前进一格
            }
        }
        else
        {
            if (!(rand() % 4))
            {
                mnDirection = rand() % 4;
                mnStop = 2;
                PrintTank();
                return;
            }
            else
            {
                int i = 0;
                int nSaveDir = mnDirection;
                for (; i < 3; i++)
                {
                    mnDirection = (mnDirection + 1) % 4;
                    if (!TankIsHit())
                    {
                        break;
                    }
                }
                if (i == 3)
                {
                    mnDirection = nSaveDir;
                    PrintTank();
                    return;
                }
                while (TankIsHit())
                {
                    mnDirection = rand() % 4;
                }
            }
        }
        PrintTank();
    }
}

void Tank::BuildBullet()
{
    if (mnCD == 0)
    {
        if (rand() % 5 == 0)
        {
            if (!mBullet.mbExist && mbExist)
            {
                switch (mnDirection)
                {
                case UP:
                    mBullet.mX = mX;
                    mBullet.mY = mY - 2;
                    break;
                case DOWN:
                    mBullet.mX = mX;
                    mBullet.mY = mY + 2;
                    break;
                case LEFT:
                    mBullet.mX = mX - 2;
                    mBullet.mY = mY;
                    break;
                case RIGHT:
                    mBullet.mX = mX + 2;
                    mBullet.mY = mY;
                    break;
                }
                mBullet.mnDirection = mnDirection;
                mBullet.mnInitial = 1;
                mBullet.mbExist = true;
                mBullet.mbMy = false;
                mnCD = 10;
            }
        }
    }
    else
    {
        mnCD--;
    }
}

void Tank::CotrolTank()
{
}

MyTank::MyTank()
{
    mbMyTank = true;
    mX = 15;
    mY = 38;
    mnDirection = UP;
    mbExist = true;
    mnCD = 7;
    mnModel = 0;
    PrintTank();

}
MyTank::~MyTank()
{
}

void MyTank::ReveieTank()
{
    if (mnReviveCnt < 4 && !mbExist)
    {
        mX = 15;
        mY = 38;
        if (BirthPosCheck(mX, mY))
        {
            mnDirection = UP;
            mbExist = true;
            mnReviveCnt++;
            PrintTank();
        }
    }
}

void MyTank::BuildBullet()
{
    if (mBullet.mbExist == false && mbExist)
    {
        switch (mnDirection)
        {
        case UP:
            mBullet.mX = mX;
            mBullet.mY = mY - 2;
            break;
        case DOWN:
            mBullet.mX = mX;
            mBullet.mY = mY + 2;
            break;
        case LEFT:
            mBullet.mX = mX - 2;
            mBullet.mY = mY;
            break;
        case RIGHT:
            mBullet.mX = mX + 2;
            mBullet.mY = mY;
            break;
        }
        mBullet.mnDirection = mnDirection;
        mBullet.mnInitial = 1;
        mBullet.mbExist = true;
        mBullet.mbMy = true;
    }
}

void MyTank::CotrolTank()
{
    bool bIsPress = false;
    int nSaveX = mX;
    int nSaveY = mY;

    if (!mbExist)
    {
        return;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        mnDirection = UP;
        bIsPress = true;
        nSaveY--;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        mnDirection = DOWN;
        bIsPress = true;
        nSaveY++;
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        mnDirection = LEFT;
        bIsPress = true;
        nSaveX--;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        mnDirection = RIGHT;
        bIsPress = true;
        nSaveX++;
    }
    if (bIsPress && !TankIsHit())
    {
        ClearTank();
        mX = nSaveX;
        mY = nSaveY;
    }
    PrintTank();
    if (GetAsyncKeyState(88) & 0x8000)
    {
        BuildBullet();
    }
}





