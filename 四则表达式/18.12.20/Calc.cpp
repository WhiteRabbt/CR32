#include "pch.h"
#include "Calc.h"
#include <iostream>
#include <ctype.h>

int Calc::m_table[7][7] = {

    {BIG,BIG,LOW,LOW,LOW,BIG,BIG},
    {BIG,BIG,BIG,BIG,LOW,BIG,BIG},
    {BIG,BIG,BIG,BIG,LOW,BIG,BIG},
    {BIG,BIG,BIG,BIG,LOW,BIG,BIG},
    {LOW,LOW,LOW,LOW,LOW,EQU,SKY},
    {BIG,BIG,BIG,BIG,SKY,BIG,BIG},
    {LOW,LOW,LOW,LOW,LOW,SKY,EQU},
};

Calc::Calc()
{
    char sz[] = "+-*/()#";
    int i = 0;
    for (char c : sz)
    {
        m_map[c] = i++;

    }
    m_set.insert(sz, end(sz));

}


Calc::~Calc()
{
}

int Calc::Calculator(string &trExpression)
{
    int nRetVal = 0;
    
    for (auto &c : trExpression)
    {

        //判断为数字入栈
        if (m_set.find(c) == m_set.end())
        {
            c = c - '0';
            m_num.push(c);
        }
        else
        {
            if (m_operator.empty())
            {
                m_operator.push(c);
            }
            else
            {
                IsLow(c);
            }
        }
    }

    nRetVal =  m_num.top();
    m_num.pop();

    return nRetVal;
}

void Calc::IsLow(char c)
{
    auto emRelation = Compare(c, m_operator.top());
    switch (emRelation)
    {
    case BIG:
        m_operator.push(c);
        break;
    case LOW:
        Calculate();
        IsLow(c);
        break;
    case EQU:
        m_operator.pop();
        break;
    case SKY:
        try
        {
            throw exception("表达式不匹配");;
            
        }
        catch (const std::exception& err)
        {
            cout << err.what() << endl;
            system("pause");
            exit(EXIT_FAILURE);
        }
    default:
        break;
    }
}

Calc::MyEnum Calc::Compare(const char cRow, const char cCol)
{
    int y = m_map[cRow];
    int x = m_map[cCol];

    return (MyEnum)m_table[y][x];
}

void Calc::Calculate()
{
    try
    {
        if (m_num.size() < 2)
        {
            throw exception("表达式不匹配");;
        }
    }
    catch (const std::exception& err)
    {
        cout << err.what() << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
    int nFirst = 0;
    int nSecond = 0;

    nFirst = m_num.top();
    m_num.pop();
    nSecond = m_num.top();
    m_num.pop();
    
    switch (m_operator.top())
    {
    case '+':
        m_num.push(nFirst + nSecond);
        break;
    case '-':
        m_num.push(nFirst - nSecond);
        break;
    case '*':
        m_num.push(nFirst * nSecond);
        break;
    case '/':
        m_num.push(nFirst / nSecond);
        break;
    default:
        break;
    }
    m_operator.pop();
}
