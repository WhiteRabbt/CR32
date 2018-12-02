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
    //��ʼ������
    void InitBox();


    //����X����
    void SetX(int index, int X)
    {
        m_Coords[index][0] = X;
    }

    //����Y����
    void SetY(int index, int Y)
    {
        m_Coords[index][1] = Y;
    }

    //�õ�X����
    int X(int index)const
    {
        return m_Coords[index][0];
    }

    //�õ�Y����
    int Y(int index)const
    {
        return m_Coords[index][1];
    }

    //����ת
    void RightRotate();

    //�ı�s_IStates
    void ChangeIState()
    {
        if(m_CurType == IShape)
        {
            s_IStates = -s_IStates;
        }
    }

    //������һ�����������
    void RetNextBoxCoords(int nextCoords[][2]);

   //���������
    void SetRadom();

   //������״
    void SetShape(emBoxType nType);
    
    emBoxType m_CurType ;
private:
   

private:
    //���������
    static int s_IStates ;
    int m_Coords[4][2];
   
    emBoxType m_NextType = (emBoxType)(rand() % 7 + 1);
    static const int sm_coordsTable[8][4][2];
};

