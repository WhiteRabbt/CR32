#include "pch.h"
#include "Snack.h"


Snack::Snack()
{
    COORD coord;
    coord.X = 3;
    coord.Y = 3;
    ModifyMap(coord, SNACK);
    m_vCoord.push_back(coord);
    coord.X = 4;
    ModifyMap(coord, SNACK);
    m_vCoord.push_back(coord);
    m_Dir = DOWN;
    m_foodX = 10;
    m_foodY = 10;
    MakeFood();
}


Snack::~Snack()
{
}

void Snack::SetDir(int nDir)
{
    m_Dir = nDir;
}

void Snack::InsertToBegin()
{
    static COORD coord(m_vCoord[0]);

    switch (m_Dir)
    {
    case UP:
        coord.Y--;
        break;
    case DOWN:
        coord.Y++;
        break;
    case LEFT:
        coord.X--;
        break;
    case RIGHT:
        coord.X++;
        break;
    default:
        break;
    }
    m_vCoord.push_front(coord);
    ModifyMap(coord,SNACK);
}

void Snack::DelEndElment()
{
    ModifyMap(m_vCoord[m_vCoord.size() - 1],SPACE);
    m_vCoord.pop_back();
}


COORD Snack::GetBeginElment()
{
    return m_vCoord[0];
}

COORD Snack::GetEndElment()
{
    return m_vCoord[m_vCoord.size()-1];
}

bool Snack::HitCheak()
{
    int x = m_vCoord[0].X;
    int y = m_vCoord[0].Y;
    bool bRet = false;

    switch (m_Dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    }
    if (g_arrMap[y][x] == SNACK)
    {
        bRet = true;
    }
    else if (g_arrMap[y][x] == WALL)
    {
        bRet = true;
    }
    return bRet;
}

bool Snack::EatFoodCheak()
{
    int x = m_vCoord[0].X;
    int y = m_vCoord[0].Y;
    bool bRet = false;

    switch (m_Dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    }
    if (g_arrMap[y][x] == FOOD)
    {
        bRet = true;
        g_arrMap[y][x] = SNACK;
    }
   
    return bRet;
}


void Snack::ModifyMap(COORD coord, int nVal)
{
    g_arrMap[coord.Y][coord.X] = nVal;
}

void Snack::MakeFood()
{
    while (g_arrMap[m_foodY][m_foodX] == SNACK)
    {
        m_foodX = rand() % (WIDTH - 2) + 1;
        m_foodY = rand() % (HEIGHT - 2) + 1;
    }
    g_arrMap[m_foodY][m_foodX] = FOOD;
}

COORD Snack::GetFoodCoord()
{
    return COORD{ m_foodX,m_foodY };
}
