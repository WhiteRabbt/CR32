#pragma once
#include <iostream>


using namespace std;
class MakeName
{
public:
    MakeName();
    ~MakeName();



    int m_nPre;
    int m_nLast;
    char  m_arrPreName[500][5];
    char  m_arrLastName[5000][5];
};

