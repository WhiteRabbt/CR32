#pragma once
#include "Tetris.h"
#include <Windows.h>
#define HEIGTH 24
#define WIDTH 12
#define BLOCK 1
#define WALL 2
#define SPACE 0

class Sense
{
public:
    Sense() = default;
    ~Sense();
public:
   
    //��ʼ������
    void InitSense(Box &box);

    //��Ϸ����
    int GameIsOver();

    //��ʾ��Ϸ����
    void ShowBg();

    //��ʾ����
    void ShowBox(const Box &box);

    //���÷���
    void SetBox(const Box &tBox);

    //����
    void Down( Box &tBox);

    //�ж��Ƿ�����ƶ�
    int IsMove(int x, int y, const Box &tBox);

    //���ٷ���
    void DestroyBox(const Box &tBox);

    //���صȼ�
    int RetLevel();

    //����
    void Right(const Box &tBox);

    //����
    void Lfet(const Box &tBox);

    //��ת
    void Rotate( Box &tBox);
 

    //����
    void DestroyLine();

    //�����ڿ���̨���λ��
    void MySetConsoleCursorPos(int x,int y);
private:
    //��ʼ���߿�
    void Init();

    //�����Ӻ���
    void CopyArr(int index);
private:
    COORD cursorPos;
    int m_SenseX = 3;
    int m_SenseY = 0;
    static int sm_nScore ;
    static int sm_nLevel ;
    static int sm_Frame[HEIGTH][WIDTH];
};

