#pragma once
#include <map>
#include <set>
#include <stack>
#include "MyStack.h"
#include <assert.h>
#define T_LIST
using namespace std;

class Calc
{
public:
    Calc();
    ~Calc();

    enum MyEnum
    {
        BIG,LOW,EQU,SKY
    };

    int Calculator(string &trExpression);

    void IsLow(char c);

    MyEnum Compare(const char cRow, const char cCol);

private:
    void Calculate();
private:
    map<char, int>      m_map;
    set<char>           m_set;
    MyStack<char>         m_operator;
    MyStack<int>          m_num;
    static int          m_table[7][7];
};





//»ØÎÄÐòÁÐ abcdcba
