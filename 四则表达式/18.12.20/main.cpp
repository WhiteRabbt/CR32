// 18.12.20.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Calc.h"

using namespace std;

int main()
{
    int nSum = 0;
    string str("#9*4+3*2#");
    Calc calc;
    nSum =  calc.Calculator(str);

    MyStack<int> ll;
    for (int i = 0; i < 5; i++)
    {
        ll.push(i);

    }for (int i = 0; i < 5; i++)
    {
        //ll.pop(;

    }




    std::cout << "Hello World!\n"; 
    system("pause");
}

