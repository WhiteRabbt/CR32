#include "Sense.h"
#include <stdio.h>
#include <Windows.h>



Sense::~Sense()
{
}
//定义类静态数据
int Sense::sm_Frame[HEIGTH][WIDTH];
int Sense::sm_nScore = 0;
int Sense::sm_nLevel = 1;

void Sense::Init()
{
    for (int i = 0; i < HEIGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            sm_Frame[i][j] = SPACE;
        }
    }
    for (int i = 0; i < HEIGTH - 1; i++)
    {
        sm_Frame[i][0] = WALL;
        sm_Frame[i][WIDTH - 1] = WALL;
    }
    for (int j = 0; j < WIDTH; j++)
    {
        sm_Frame[HEIGTH - 1][j] = WALL;
    }
}

void Sense::InitSense(Box &box)
{
    Init();
    int sm_nScore = 0;
    int sm_nLevel = 1;
}

int Sense::GameIsOver()
{
    for (int i = 1; i < WIDTH - 1; i++)
    {
        if (WALL == sm_Frame[4][i])
        {
            MySetConsoleCursorPos(6, 12);
            printf("Game Over!");
            MySetConsoleCursorPos(6, 13);
            printf("重新开始--Y键");
            MySetConsoleCursorPos(6, 14);
            printf("退出--N键");
            return 1;
        }
    }
    return 0;
}

void Sense::ShowBg()
{
    MySetConsoleCursorPos(0, 4);
    for (int i = 4; i < HEIGTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (sm_Frame[i][j] == WALL || sm_Frame[i][j] == BLOCK)
            {
                printf("■");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
    MySetConsoleCursorPos((WIDTH + 4)*2, 10);
    printf("<游戏说明>");
    MySetConsoleCursorPos((WIDTH + 4) * 2, 11);
    printf("↑  旋转");
    MySetConsoleCursorPos((WIDTH + 4) * 2, 12);
    printf("←  左移");
    MySetConsoleCursorPos((WIDTH + 4) * 2, 13);
    printf("→  右移");
    MySetConsoleCursorPos((WIDTH + 4) * 2, 14);
    printf("↓  下移");
    MySetConsoleCursorPos((WIDTH + 4) * 2, 15);
    printf("当前分数:0");
    MySetConsoleCursorPos((WIDTH + 4) * 2, 16);
    printf("当前等级:1");
    MySetConsoleCursorPos((WIDTH + 4) * 2, 17);
    printf("下一个方块:");


}

void Sense::ShowBox(const Box &box)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < 4; i++)
    {
        x = (m_SenseX + box.X(i) + 1) * 2;
        y = m_SenseY + box.Y(i) + 1;
        MySetConsoleCursorPos(x, y);
        printf("■");
    }
}

void Sense::SetBox(const Box &tBox)
{
    for (int i = 0; i < 4; i++)
    {
        sm_Frame[m_SenseY + tBox.Y(i) + 1][m_SenseX + tBox.X(i) + 1] = BLOCK;
    }
}

void Sense::Down( Box &tBox)
{
    if (IsMove(m_SenseX,m_SenseY+1,tBox))
    {
        DestroyBox(tBox);
        m_SenseY++;
        for (int i = 0; i < 4; i++)
        {
            sm_Frame[m_SenseY + tBox.Y(i) + 1][m_SenseX + tBox.X(i) + 1] = BLOCK;
        }
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        sm_Frame[m_SenseY + tBox.Y(i) + 1][m_SenseX + tBox.X(i) + 1] = WALL;
    }
    DestroyLine();
    //tBox.InitBox();
    tBox.SetRadom();
    tBox.SetShape(tBox.m_CurType);


    //显示下一个方块 MySetConsoleCursorPos((WIDTH + 4) * 2, 17);
    static const int nextBoxX = (WIDTH + 4) * 2;
    static const int nextBoxY = 19;
    static int arrNextBox[4][2];
    int x = 0;
    int y = 0;

    //清除下一个方块在屏幕的图案
    for (int i = 0; i < 4; i++)
    { 
        MySetConsoleCursorPos(nextBoxX, nextBoxY + i);
        for (int j = 0; j < 4; j++)
        {
            printf("  ");
        }
    }
    //得到一个个方块坐标
    tBox.RetNextBoxCoords(arrNextBox);
    for (int i = 0; i < 4; i++)
    {
        x = nextBoxX + (arrNextBox[i][0] + 1) * 2;
        y = nextBoxY + arrNextBox[i][1] + 1;
        MySetConsoleCursorPos(x, y);
        printf("■");
    }
    
    //重置坐标
    m_SenseX = 5;
    m_SenseY = 0;
    SetBox(tBox);



}

int Sense::IsMove(int x, int y,const Box &tBox)
{
    for (int i = 0; i < 4; i++)
    {
        if (sm_Frame[y + tBox.Y(i) + 1][x + tBox.X(i) + 1] == WALL)
        {
            return 0;
        }
    }
    return 1;
}

void Sense::DestroyBox(const Box & box)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < 4; i++)
    {
        x = (m_SenseX + box.X(i) + 1) * 2;
        y = m_SenseY + box.Y(i) + 1;
        MySetConsoleCursorPos(x, y);
        printf("  ");
    }
    for (int i = 0; i < 4; i++)
    {
        sm_Frame[m_SenseY + box.Y(i) + 1][m_SenseX + box.X(i) + 1] = SPACE;
    }
}

int Sense::RetLevel()
{
    return sm_nLevel;
}

void Sense::Right(const Box &tBox)
{

    if (IsMove(m_SenseX + 1, m_SenseY, tBox))
    {
        DestroyBox(tBox);
        m_SenseX++;
        for (int i = 0; i < 4; i++)
        {
            sm_Frame[m_SenseY + tBox.Y(i) + 1][m_SenseX + tBox.X(i) + 1] = BLOCK;
        }
        
    }
}

void Sense::Lfet(const Box & tBox)
{

    if (IsMove(m_SenseX - 1, m_SenseY, tBox))
    {
        DestroyBox(tBox);
        m_SenseX--;
        for (int i = 0; i < 4; i++)
        {
            sm_Frame[m_SenseY + tBox.Y(i) + 1][m_SenseX + tBox.X(i) + 1] = BLOCK;
        }
        return;
    }
}

void Sense::Rotate(Box &tBox)
{
    Box tTempBox = tBox;
    tTempBox.RightRotate();
    if (IsMove(m_SenseX, m_SenseY, tTempBox))
    {
        tTempBox.ChangeIState();
        DestroyBox(tBox);
        tBox.RightRotate();
        SetBox(tBox);
    }
}

void Sense::DestroyLine()
{
    int nTrue = 1;
   

    for (int i = 4; i < HEIGTH - 1; i++)
    {
        for (int j = 1, cnt = 0; j < WIDTH - 1; j++)
        {
            if (sm_Frame[i][j] == WALL)
            {
                cnt++;
            }
            if (cnt == WIDTH - 2)
            {
                nTrue = 0;
                sm_nScore += 10;
                CopyArr(i);
                i--;
            }

        }
    }
    if (nTrue == 0)
    {
        MySetConsoleCursorPos(0, 4);
        for (int i = 4; i < HEIGTH; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if ((sm_Frame[i][j] == WALL) || (sm_Frame[i][j] == BLOCK))
                {
                    printf("■");
                }
                else
                {
                    printf("  ");
                }
            }
            printf("\n");
        }
        //打印分数和等级
        MySetConsoleCursorPos((WIDTH + 4) * 2, 15);
        printf("当前分数:%d",sm_nScore);
        sm_nLevel = sm_nScore / 100 + 1;
        MySetConsoleCursorPos((WIDTH + 4) * 2, 16);
        printf("当前等级:%d",sm_nLevel);
    }
}

void Sense::MySetConsoleCursorPos(int x, int y)
{
    cursorPos.X = x;
    cursorPos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}

void Sense::CopyArr(int index)
{
    for (int i = index; i > 0; i--)
    {
        for (int j = 1; j < WIDTH - 1; j++)
        {
            sm_Frame[i][j] = sm_Frame[i - 1][j];
        }
    }
}


