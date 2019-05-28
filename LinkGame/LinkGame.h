#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LinkGame.h"
#include <QIntValidator>
#include <Windows.h>

#define MAX_X   19
#define MAX_Y   11
#define BOXWIFTH 30

class LinkGame : public QMainWindow
{
    Q_OBJECT

public:
    LinkGame(QWidget *parent = Q_NULLPTR);
    int m_x;
    int m_y;
    HWND m_hwndGame;
    HANDLE m_hProcessDst;
    BYTE m_aChess[11][19];

    void StartGame();
    void InitProc();
    int isBlocked(int x, int y);
    int Remove(int x1, int y1, int x2, int y2);
    bool horizon(int x1, int y1, int x2, int y2);
    int vertical(int x1, int y1, int x2, int y2);
    int turn_once(int x1, int y1, int x2, int y2);
    int turn_twice(int x1, int y1, int x2, int y2);

    //设置速度
    void SetGameSpeed();

    bool SeekSameCheek(int x, int y);
    //继承虚函数
   


private:
    Ui::LinkGameClass ui;
};
