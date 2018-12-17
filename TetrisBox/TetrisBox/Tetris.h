#pragma once
#include <time.h>
#include <stdlib.h>

class Box
{
public:
    enum emBoxType
    {
        NoShape = 0,
        ZShape,
        SShape,
        IShape,
        TShape,
        MirroredLShape,
        SquareShape,
        LShape,
    };
    //初始化方块
    void InitBox();


    //设置X坐标
    void SetX(int index, int X)
    {
        m_Coords[index][0] = X;
    }

    //设置Y坐标
    void SetY(int index, int Y)
    {
        m_Coords[index][1] = Y;
    }

    //得到X坐标
    int X(int index)const
    {
        return m_Coords[index][0];
    }

    //得到Y坐标
    int Y(int index)const
    {
        return m_Coords[index][1];
    }

    //右旋转
    void RightRotate();

    //改变s_IStates
    void ChangeIState()
    {
        if(m_CurType == IShape)
        {
            s_IStates = -s_IStates;
        }
    }

    //返回下一个方块坐标点
    void RetNextBoxCoords(int nextCoords[][2]);

   //设置随机数
    void SetRadom();

   //设置形状
    void SetShape(emBoxType nType);
    
    emBoxType m_CurType ;
private:
   

private:
    //方块坐标点
    static int s_IStates ;
    int m_Coords[4][2];
   
    emBoxType m_NextType = (emBoxType)(rand() % 7 + 1);
    static const int sm_coordsTable[8][4][2];
};

