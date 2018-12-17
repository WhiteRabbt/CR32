#pragma once
#include "GameData.h"

class Bullet 
{
public:
    Bullet() {
        mbExist = false;
    };
    ~Bullet() {};

    //���ݵ�ǰ�����ӡ�ӵ�
    void PrintBullet();
    //����ӵ�
    void ClearBullet();
    //����ӵ���ײ
    void BulletHit();
    //�ӵ��ƶ�
    void BulletFly();
    //��⵱ǰλ��
    bool BulletCheak();

//����
    int mX;
    int mY;
    bool mbMy;
    bool mbExist;
    int mnDirection;
    int mnInitial;
};



