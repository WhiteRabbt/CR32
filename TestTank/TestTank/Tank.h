#pragma once
#include "GameData.h"
#include "Bullet.h"

class Tank
{
public:
    Tank()
    {
        mX = 0;
        mY = 0;
        mbMyTank = false;
        mnDirection = DOWN;
        mbExist = 0;
        mnCD = 0;
        mnModel = 0;
        mnStop = 0;
        mnReviveCnt = 0;
    };
    ~Tank() {}
    //��Ա����
    //���ݵ�ͼ���̹���Ƿ����
    void CheckExist();
    //����̹��
    virtual void ReveieTank();
    //������λ��
    int BirthPosCheck(int x, int y);
    //��ӡ̹��(�ı���Ļ��ʾ������)
    void PrintTank();
    //̹����ײ���(Ĭ�ϵ�ǰλ�úͷ���)
    bool TankIsHit();
    //���̹��(Ĭ�ϵ�ǰλ��)(��ȥ��Ļ����������)
    void ClearTank();
    //̹���ƶ�
    void Move();
    //�����ӵ�
    virtual void BuildBullet();
    virtual void CotrolTank();

    //���ݳ�Ա
public:
    Bullet mBullet;         //�ӵ�
    int mX;                 //̹��x����(����)
    int mY;                 //̹��y����(����)
    bool mbMyTank;          //̹���б�(�ҵ�Ϊ1����Ϊ�з�̹��)
    int mnDirection;        //̹�˷���
    bool mbExist;           //̹���Ƿ����
    int mnReviveCnt;        //̹�˸������
    int mnCD;               //̹�˷����ӵ�CD
    int mnModel;            //̹��ģ��
    int mnStop;             //̹���ƶ�״̬

};
//�ҷ�̹����
class MyTank :public Tank
{
public:
    MyTank();
    ~MyTank();
    void ReveieTank()override;
    void BuildBullet()override;
    void CotrolTank();
};






