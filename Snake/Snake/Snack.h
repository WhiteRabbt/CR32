#pragma once
#include "Const.h"
#include <Windows.h>
#include <deque>

using namespace std;
class Snack
{
public:
    Snack();
    ~Snack();
    //���÷���
    void SetDir(int nDir);

    //���ݷ������һ����Ԫ��
    void InsertToBegin();

    //ɾ�����һ��Ԫ��
    void DelEndElment();

    //�õ���Ԫ��
    COORD GetBeginElment();

    //�õ�βԪ��
    COORD GetEndElment();

    //�����ײ
    bool HitCheak();

    //�Ե�ʳ����
    bool EatFoodCheak();

    //����ʳ��
    void MakeFood();

    //�õ�ʳ������
    COORD GetFoodCoord();
private:

    //�����޸ĵ�ͼ����
    void ModifyMap(COORD coord, int nVal);

private:
    deque<COORD> m_vCoord;
    int m_Dir;
    short m_foodX;
    short m_foodY;
};

