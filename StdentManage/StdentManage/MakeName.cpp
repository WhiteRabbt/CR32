#include "pch.h"
#include "MakeName.h"
#include "ManageSystem.h"


MakeName::MakeName()
{
    //读取百家姓
    FILE* pf = fopen("preName.txt", "rb");
    rewind(pf);
    fread(&m_nPre, sizeof(int), 1, pf);
    fread(&m_nLast, sizeof(int), 1, pf);
    fread(&m_arrPreName, 5, m_nPre, pf);
    fread(&m_arrLastName, 5, m_nLast, pf);
    fclose(pf);
    //生成名字
    pf = fopen("Name.txt", "w+");
    assert(pf != nullptr);
    CMyString str;
    int nOffset = 0;
    for(int i = 0;i <5;i++)
    {
        nOffset = ftell(pf);
        fprintf(pf,"%d\n", nOffset);
        fprintf(pf,"%d\n", i);
        str = m_arrPreName[rand() % m_nPre];
        str = str+ m_arrLastName[rand() % m_nLast];
        fprintf(pf, "%s\n",str.c_str());
    }
    fclose(pf);
  
}


MakeName::~MakeName()
{
}
