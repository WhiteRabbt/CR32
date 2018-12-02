#include "Tetris.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>






int Box::s_IStates = 1;

void Box::InitBox()
{
    SetRadom();
    SetShape(m_CurType);
    s_IStates = 1;
}

 void Box::RightRotate()
{
     static int OneCoords[4][2] = { { 0, -1 }, { 0, 0 }, { 0, 1 }, { 0, 2 } };
     static int TwoCoords[4][2] = { { -1, 0,}, {0, 0},{1, 0},{2, 0} };
     int coords[4][2];

     memcpy(coords, m_Coords, sizeof(coords));
     //田字形不旋转直接返回
     if (MirroredLShape == m_CurType)
     {
         return;
     }

     //如果是I形状自己定义旋转
     if (IShape == m_CurType )
     {
         if (s_IStates == 1)
         {
             memcpy(m_Coords, TwoCoords, sizeof(TwoCoords));
             s_IStates = -1;
         }
         else
         {
             memcpy(m_Coords, OneCoords, sizeof(OneCoords));
             s_IStates = 1;
         }
         return;
     }
     
     //(Y坐标变负赋给X坐标.X坐标不变赋给Y)
     for (int i = 0; i < 4; ++i)
     {
         SetX(i, -coords[i][1]);
         SetY(i, coords[i][0]);
     }
   
}

 void Box::RetNextBoxCoords(int nextCoords[][2])
 {
     memcpy(nextCoords,sm_coordsTable[m_NextType], sizeof(int)*8);
 }

 void Box::SetRadom()
{
    m_CurType = m_NextType;
    m_NextType = (emBoxType)(rand() % 1/* 7 + 1*/);
}

//设置形状
void Box::SetShape(emBoxType nType)
{
   
    for (int i = 0; i < 4; i++)
    {
        m_Coords[i][0] = sm_coordsTable[nType][i][0];
        m_Coords[i][1] = sm_coordsTable[nType][i][1];
    }
}
 const int Box::sm_coordsTable[8][4][2] = {
       { { 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 } },
       { { 0, -1 },{ 0, 0 },{ -1, 0 },{ -1, 1 } },
       { { 0, -1 },{ 0, 0 },{ 1, 0 },{ 1, 1 } },
       { { 0, -1 },{ 0, 0 },{ 0, 1 },{ 0, 2 } },
       { { -1, 0 },{ 0, 0 },{ 1, 0 },{ 0, 1 } },
       { { 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 } },
       { { -1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } },
       { { 1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } }
};
    