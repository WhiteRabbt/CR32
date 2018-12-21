#include "pch.h"
#include "Sence.h"
#include <iostream>


Sence::Sence()
{
    InitData();
    PrintInterface();
}


Sence::~Sence()
{
}

void Sence::InitData()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || (i == HEIGHT - 1) || j == 0 || (j == WIDTH - 1))
            {
                g_arrMap[i][j] = WALL;
            }
        }
    }
}

void Sence::MoveCursor(int x,int y)
{
    COORD coord = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Sence::PrintInterface()
{
    system("mode con cols=80 lines=40");
    CONSOLE_CURSOR_INFO cursorInfo = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (g_arrMap[i][j] == WALL)
            {
                printf("¡ö");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
    PrintHead();
    PrintTall("¡ö");
    PrintFood();
}

void Sence::PrintHead()
{
    int x = m_snack.GetBeginElment().X;
    int y = m_snack.GetBeginElment().Y;
    MoveCursor(x * CHAR_WHIDTH, y);
    printf("¡ö");
}

void Sence::PrintTall(const char* psz )
{
    int x = m_snack.GetEndElment().X;
    int y = m_snack.GetEndElment().Y;
    MoveCursor(x * CHAR_WHIDTH, y);
    printf("%s",psz);

}

void Sence::PrintFood()
{
    COORD coord = m_snack.GetFoodCoord();
    MoveCursor(coord.X * 2, coord.Y);
    printf("¡ï");
}

void Sence::Keyboard()
{
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        m_snack.SetDir(UP);
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        m_snack.SetDir(DOWN);
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        m_snack.SetDir(LEFT);
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        m_snack.SetDir(RIGHT);
    }
}

void Sence::GameLogic()
{
    if (m_snack.HitCheak())
    {
        MoveCursor(15, 15);
        printf("Game Over");
        while (1)
        {
            continue;
        }
    }
    if (!m_snack.EatFoodCheak())
    {
        PrintTall();
        m_snack.DelEndElment();
    }
    else
    {
        m_snack.MakeFood();
        PrintFood();
    }
    m_snack.InsertToBegin();
    PrintHead();

}
