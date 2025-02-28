// TetrisBox.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include "Sense.h"
#include "Tetris.h"
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
using namespace std;
void StartGame();
int main()
{
    

    srand(time(0));
    StartGame();
    //std::cout << "Hello World!\n"; 
}

void StartGame()
{
    //隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo = { 1,0 };
    HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(hWnd, &cursorInfo);
    COORD coord = {
        60,16
    };

    //初始化状态
    Box tBox;
    Sense tSense;
    tBox.InitBox();
    tSense.InitSense(tBox);
    tSense.SetBox(tBox);
    tSense.ShowBg();
    tSense.ShowBox(tBox);


    double t = 1000;
    int ch1 = '\0';
    int ch2 = '\0';
    const char *pCh1 = NULL;
    const char *pCh2 = NULL;
    int nGameState = 0;
    //
    clock_t currentTime = 0;
    clock_t previousTime = 0;
    long timeDiff = 0l;

    while (1)
    {
        //获得当前处理器时间
       previousTime = clock();
        while (1)
        {
            do
            {
                currentTime = clock();
                if (kbhit())
                {
                    ch1 = getch();
                    ch2 = getch();
                    if (strchr("HPKM", ch2) || strchr("yYnN", ch1))
                    {
                        break;
                    }
                }
                timeDiff = currentTime - previousTime;
            } while (timeDiff < t);



            if (timeDiff >= t)
            {

                tSense.Down(tBox);
                tSense.ShowBox(tBox);
                nGameState = tSense.GameIsOver();
                previousTime = clock();
#ifndef _DEBUG
                //调试打印时间
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                printf("%ld", timeDiff);
#endif // _DEBUG
                t = 1000 - (tSense.RetLevel() - 1) * 200;
            }
            else
            {
                if ((ch1 == 'y' || ch1 == 'Y') && nGameState == 1)
                {
                    system("cls");
                    StartGame();
                    return;
                }
                if ((ch1 == 'n' || ch1 == 'N') && nGameState == 1)
                {
                    goto PROC_END;
                }
                switch (ch2)
                {
                case 72:
                    tSense.Rotate(tBox);
                    tSense.ShowBox(tBox);
                    break;
                case 75:
                    tSense.Lfet(tBox);
                    tSense.ShowBox(tBox);
                    break;
                case 77:
                    tSense.Right(tBox);
                    tSense.ShowBox(tBox);
                    break;
                case 80:
                    tSense.Down(tBox);
                    tSense.ShowBox(tBox);
                    nGameState = tSense.GameIsOver();
                    break;
                }
            }
        }
    }
PROC_END:
    return;
}