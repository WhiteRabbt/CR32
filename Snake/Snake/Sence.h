#pragma once
#include "Const.h"
#include "Snack.h"
#include <Windows.h>
#define CHAR_WHIDTH 2

class Sence
{
public:
    Sence();
    ~Sence();

    //GameLogic
    void GameLogic();

    //���ܼ���
    void Keyboard();
private:
    //��ʼ����ͼ����
    void InitData();

    //�ƶ����
    void MoveCursor(int x, int y);

    //��ӡ��Ϸ����
    void PrintInterface();

    //��ӡͷ��
    void PrintHead();

    //��ӡβ��
    void  PrintTall(const char* psz = "  ");

    //��ӡʳ��
    void PrintFood();

   

private:
    Snack m_snack;

};

