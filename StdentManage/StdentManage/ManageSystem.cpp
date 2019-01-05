#include "pch.h"
#include "MakeName.h"
#include "ManageSystem.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include "Mystl.h"

#define MAX_SIZE 100
#define SAFE_OPEN(pf) if(pf == nullptr){throw runtime_error("���ļ�ʧ��");}
#define SAFE_PROC(pf) if(pf != nullptr){fclose(pf);}
char* Fgets_S(char *pBuffer, int nMaxCount, FILE *pStream);

void Manage::InsertStu(StuID &ref)
{
    m_treeIDStudentName.Insert(ref.m_nID, ref);
    m_treeStudentNameID.Insert(ref.m_strName, ref);
}

void Manage::PrintStu()
{
    int i = 0;
    for (auto student : m_treeIDStudentName)
    {
        printf("ѧ��ID %d,���� %s\n", student.m_nID, student.m_strName.c_str());
    }
}

int Manage::Menu()
{
    int ch = 0;
    system("cls");
    printf("a.����ID����ѧ������.\n\n");
    printf("b.����ѧ����������ID.\n\n");
    printf("c.����γ�ID��ѯ�γ���.\n\n");
    printf("d.����γ�����ѯ�γ�ID.\n\n");
    printf("e.����γ�ID��ѯѡ���˸ÿγ̵�ѧ���Լ��ɼ�.\n\n");
    printf("f.����ѧ��ID��ѯ��ѧ��ѡ�޵Ŀγ���Ϣ.\n\n");
    printf("g.����ѧ��(ID, ����).\n\n");
    printf("h.�����γ�(ID,����).\n\n");
    printf("i.����ѡ�μ�¼(ѧ��ID, �γ�ID, ����).\n\n");
    printf("j.ɾ��ѧ��(ID, ����).\n\n");
    printf("k.ɾ���γ�(ID,����).\n\n");
    printf("L.ɾ��ѡ�μ�¼(ѧ��ID, �γ�ID, ����).\n\n");
    printf("q.�˳�.\n\n");

    while (true)
    {
        if (_kbhit())
        {
            ch = _getch();
            ch = tolower(ch);
            if (strchr("abcdefghijklq", ch))
            {
                break;
            }
        }
    }
    return ch;
}

void Manage::FindStudentName()
{
    int nID = 0;
    system("cls");
    printf("������ѧ��ID :");
    UserInput(&nID);
    auto pRet = m_treeIDStudentName.Find(nID);
    if (pRet)
    {
        printf("ѧ������  :  %s\r\n", pRet->m_val.m_strName.c_str());
    }
    else
    {
        printf("û���ҵ�.\r\n");
    }
    system("pause");
}

void Manage::FindStudentID()
{
    system("cls");
    char szBuffer[MAX_SIZE] = "";
    printf("����ѧ������ :");
    scanf("%100s", szBuffer);
    auto pRet = m_treeStudentNameID.Find(szBuffer);
    if (pRet)
    {
        while (pRet)
        {
            printf("ѧ��ID  :  %d\r\n", pRet->m_val.m_nID);
            pRet = pRet->m_pNext;
        }
    }
    else
    {
        printf("û���ҵ�.\r\n");
    }
    system("pause");
}

void Manage::FindLessonName()
{
    int nID = 0;
    system("cls");
    printf("����γ�ID :");
    UserInput(&nID);
    auto pRet = m_treeIDCourseName.Find(nID);
    if (pRet)
    {
        printf("�γ���  :  %s\r\n", pRet->m_val.m_strLesson.c_str());
    }
    else
    {
        printf("û���ҵ�.\r\n");
    }
    system("pause");
}

void Manage::FindLessonID()
{
    char szBuffer[MAX_SIZE] = "";

    system("cls");
    printf("������γ��� :");
    scanf("%100s", szBuffer);
    auto pRet = m_treeCourseNameID.Find(szBuffer);
    if (pRet)
    {
        printf("�γ�ID  :  %d\r\n", pRet->m_val.m_nID);
    }
    else
    {
        printf("û���ҵ�.\r\n");
    }
    system("pause");
}

void Manage::FindStudentScore()
{
    int nCourseID = 0;
    int ch = 0;
    system("cls");
    printf("����γ�ID :");
    UserInput(&nCourseID);
    auto pRet = m_treeCourseIDScore.Find(nCourseID);
    if (pRet != nullptr)
    {
        const char *pName = nullptr;
        const char *pStudentName = nullptr;
        for (int i = 1; pRet != nullptr; i++, pRet = pRet->m_pNext)
        {
            pName = FindCourseName(nCourseID);
            pStudentName = FindStudentName(pRet->m_val.m_nStuID);
            printf("�γ��� : %-15s  ѧ��ID : %-6d ѧ������ : %-5s  �ɼ� : %d\n\n", pName,pRet->m_val.m_nStuID, pStudentName, pRet->m_val.m_nScore);
            if (i % 10 == 0)
            {
                printf("�������һҳ,q����.");
                ch = getchar();
                if (ch == 'q')
                {
                    return;
                }
                else
                {
                    system("cls");
                }
            }
        }
    }
    else
    {
        printf("û���ҵ�.\r\n");
    }
    system("pause");
}

void Manage::FindStudentInfo()
{
    int nStudentID = 0;
    int i = 1;
    int ch = 0;

    system("cls");
    printf("����ѧ��ID :");
    UserInput(&nStudentID);
    auto pRet = m_treeStudentIDInfo.Find(nStudentID);

    if (pRet != nullptr)
    {
        const char *pStudentName = FindStudentName(nStudentID);
        const char *pCourseName = nullptr;
        printf("ѧ��ID : %d  ѧ������ : %s\n", nStudentID, pStudentName);
        while ( pRet != nullptr )
        {
            pCourseName = FindCourseName(pRet->m_val.m_nCourseID);
            printf("�γ�ID : %-6d   �γ��� : %-15s    �ɼ� : %d\n\n", pRet->m_val.m_nCourseID, pCourseName, pRet->m_val.m_nScore);
            pRet = pRet->m_pNext;
            if (i++ % 10 == 0)
            {
                printf("�������һҳ,q����.");
                ch = getchar();
                if (ch == 'q')
                {
                    return;
                }
                else
                {
                    system("cls");
                }
            }
        }
    }
    else
    {
        printf("û���ҵ�.\r\n");
    }
    system("pause");
}

void Manage::AddStudent()
{
    system("cls");
    char szName[MAX_SIZE] = "";
    int nID = 0;
    printf("����ѧ������: ");
    scanf("%s",szName);
    printf("����ѧ��ID: ");
    UserInput(&nID);
    fseek(m_pfName, 0, SEEK_END);
    int nOffset = ftell(m_pfName);
    fprintf(m_pfName, "%d\n%d\n%s\n", nOffset, nID, szName);
    m_treeIDStudentName.Insert(nID,{ nOffset,nID ,szName });
    m_treeStudentNameID.Insert(szName,{ nOffset,nID ,szName });
    fflush(m_pfName);
}

void Manage::AddCourse()
{
    system("cls");
    char szName[MAX_SIZE] = "";
    int nID = 0;
    printf("����γ���: ");
    scanf("%s", szName);
    printf("����γ�ID: ");
    UserInput(&nID);
    fseek(m_pfLesson, 0, SEEK_END);
    int nOffset = ftell(m_pfLesson);
    fprintf(m_pfLesson, "%d\n%d\n%s\n", nOffset, nID, szName);
    m_treeCourseNameID.Insert(szName, { nOffset,nID ,szName });
    m_treeIDCourseName.Insert(nID, { nOffset,nID ,szName });
    fflush(m_pfLesson);
}

void Manage::AddCourseRecord()
{
    system("cls");
    IDScore tagIDscore;
    printf("����γ�ID: ");
    UserInput(&tagIDscore.m_nCourseID);
    printf("����ѧ��ID: ");
    UserInput(&tagIDscore.m_nStuID);
    printf("����ѧ������: ");
    UserInput(&tagIDscore.m_nScore);
    //д���ļ�
    fseek(m_pfIDScore, 0, SEEK_END);
    tagIDscore.m_nOffset = ftell(m_pfIDScore);
    fprintf(m_pfIDScore, "%d\n%d\n%d\n%d\n", tagIDscore.m_nOffset, tagIDscore.m_nCourseID,tagIDscore.m_nStuID, tagIDscore.m_nScore);
    //������
    AddCourseRecord(tagIDscore);
    fflush(m_pfIDScore);
}

void Manage::DelStudent()
{
    system("cls");
    int nID = 0;
    char szName[MAX_SIZE] = "";
    printf("����ѧ��ID: ");
    UserInput(&nID);
    printf("����ѧ������: ");
    scanf("%s", szName);
    auto pRet = m_treeIDStudentName.Find(nID);
    if (pRet)
    {
        //���ļ���ɾ������
        auto tagTemp = pRet->m_val;
        int nLength = 0;
        char szTemp[MAX_SIZE] = "";
        fseek(m_pfName, tagTemp.m_nOffest, SEEK_SET);
        _itoa(tagTemp.m_nOffest, szTemp, 10);
        nLength += strlen(szTemp);
        _itoa(tagTemp.m_nID, szTemp, 10);
        nLength += strlen(szTemp);
        nLength += tagTemp.m_strName.size();
        for (int i = 0; i < nLength + 6; i++)
        {
            putc(32, m_pfName);
        }
        fflush(m_pfName);
        //������ɾ������
        m_treeIDStudentName.Delete(tagTemp.m_nID);
        m_treeStudentNameID.Delete(tagTemp.m_strName);
        DelStudentRecord(tagTemp);
    }
    else
    {
        printf("û�п�ɾ����\r\n");
        system("pause");
    }
}

void Manage::DelCourse()
{
    system("cls");
    int nID = 0;
    char szName[MAX_SIZE] = "";
    printf("����γ�ID: ");
    UserInput(&nID);
    printf("����γ���: ");
    scanf("%s", szName);
    auto pRet = m_treeIDCourseName.Find(nID);
    if (pRet)
    {
        //���ļ���ɾ������
        auto tagTemp = pRet->m_val;
        int nLength = 0;
        char szTemp[MAX_SIZE] = "";
        fseek(m_pfLesson, tagTemp.m_nOffest, SEEK_SET);
        _itoa(tagTemp.m_nOffest, szTemp, 10);
        nLength += strlen(szTemp);
        _itoa(tagTemp.m_nID, szTemp, 10);
        nLength += strlen(szTemp);
        nLength += tagTemp.m_strLesson.size();
        for (int i = 0; i < nLength + 6; i++)
        {
            putc(32, m_pfLesson);
        }
        fflush(m_pfLesson);
        //������ɾ������
        m_treeIDCourseName.Delete(tagTemp.m_nID);
        m_treeCourseNameID.Delete(tagTemp.m_strLesson);
        DelLessonRecord(tagTemp);
    }
    else
    {
        printf("û�п�ɾ����\r\n");
        system("pause");
    }
}

void Manage::DelRecord()
{
    system("cls");
    IDScore idScore;
    char szName[MAX_SIZE] = "";
    printf("����γ�ID: ");
    UserInput(&idScore.m_nCourseID);
    printf("����ѧ��ID: ");
    UserInput(&idScore.m_nStuID);
    auto pNodeOne = m_treeStudentIDInfo.Find(idScore.m_nStuID);
    auto pNodeTwo = m_treeCourseIDScore.Find(idScore.m_nCourseID);
    if (pNodeOne && pNodeTwo)
    {
        //�ļ���ɾ��
        int nLength = 0;
        char szTemp[MAX_SIZE] = "";
        while (pNodeOne->m_val.m_nCourseID != idScore.m_nCourseID)
        {
            pNodeOne = pNodeOne->m_pNext;
        }
        while (pNodeTwo->m_val.m_nStuID != idScore.m_nStuID)
        {
            pNodeTwo = pNodeTwo->m_pNext;
        }
        idScore = pNodeOne->m_val;
        nLength += strlen(_itoa(idScore.m_nOffset, szTemp, 10));
        nLength += strlen(_itoa(idScore.m_nCourseID, szTemp, 10));
        nLength += strlen(_itoa(idScore.m_nStuID, szTemp, 10));
        nLength += strlen(_itoa(idScore.m_nScore, szTemp, 10));
        fseek(m_pfIDScore, idScore.m_nOffset, SEEK_SET);
        for (int i = 0; i < nLength + 8; i++)
        {
            putc(32, m_pfIDScore);
        }
        fflush(m_pfIDScore);
        //����ɾ��
        m_treeStudentIDInfo.Delete(pNodeOne);
        m_treeCourseIDScore.Delete(pNodeTwo);
    }
    else
    {
        printf("û���ҵ�");
        system("pause");
    }
}

void Manage::AddCourseRecord(IDScore & ref)
{
    m_treeCourseIDScore.Insert(ref.m_nCourseID, ref);
    m_treeStudentIDInfo.Insert(ref.m_nStuID, ref);
}

void Manage::MakeLessonRecord()
{
    IDScore idScore;
    int nOffset = 0;
    rewind(m_pfIDScore);
    for (int i = 0; i < 1000000; i++)
    {
        idScore.m_nOffset = ftell(m_pfIDScore);
        idScore.m_nCourseID = rand() % 1300;
        idScore.m_nStuID = rand() % 100000;
        idScore.m_nScore = rand() % 101;
        fprintf(m_pfIDScore, "%d\n%d\n%d\n%d\n", idScore.m_nOffset, idScore.m_nCourseID, idScore.m_nStuID, idScore.m_nScore);
    }
    fflush(m_pfIDScore);
}

void Manage::Start()
{
    int n = 0;
    while (true)
    {
        n = Menu();
        switch (n)
        {
        case 'a':
            FindStudentName();
            break;
        case 'b':
            FindStudentID();
            break;
        case 'c':
            FindLessonName();
            break;
        case 'd':
            FindLessonID();
            break;
        case 'e':
            FindStudentScore();
            break;
        case 'f':
            FindStudentInfo();
            break;
        case 'g':
            AddStudent();
            break;
        case 'h':
            AddCourse();
            break;
        case 'i':
            AddCourseRecord();
            break;
        case 'j':
            DelStudent();
            break;
        case 'k':
            DelCourse();
            break;
        case 'l':
            DelRecord();
            break;
        case 'q':
            return;
            break;
        default:
            break;
        }
    }
}

const char * Manage::FindStudentName(int nStudentID)
{

    auto  pRet = m_treeIDStudentName.Find(nStudentID);
    if (pRet != nullptr)
    {
        return pRet->m_val.m_strName.c_str();
    }
    return nullptr;
}

const char * Manage::FindCourseName(int nCourseID)
{
    auto  pRet = m_treeIDCourseName.Find(nCourseID);
    if (pRet != nullptr)
    {
        return pRet->m_val.m_strLesson.c_str();
    }
    return nullptr;
}

void Manage::DelStudentRecord(StuID &argRef)
{
    auto pNodeStudentID = m_treeStudentIDInfo.Find(argRef.m_nID);
    while (pNodeStudentID != nullptr)
    {
        auto pNodeCourseID = m_treeCourseIDScore.Find(pNodeStudentID->m_val.m_nCourseID);
        assert(pNodeCourseID != nullptr);
        while (pNodeCourseID->m_val.m_nStuID != argRef.m_nID)
        {
            pNodeCourseID = pNodeCourseID->m_pNext;
        }
        m_treeCourseIDScore.Delete(pNodeCourseID);
        m_treeStudentIDInfo.Delete(pNodeStudentID);
        pNodeStudentID = m_treeStudentIDInfo.Find(argRef.m_nID);
    }
}

void Manage::DelLessonRecord(LessonID & argRef)
{
    //����Ҫɾ���Ŀγ�ID�Ľڵ�
    auto pNodeCourseID = m_treeCourseIDScore.Find(argRef.m_nID);
    while (pNodeCourseID != nullptr)
    {
        //ͨ��ѧ��ID���Ҳ���ѡ�޵Ŀγ�
        auto pNodeStudentID = m_treeStudentIDInfo.Find(pNodeCourseID->m_val.m_nStuID);
        assert(pNodeStudentID != nullptr);
        while (pNodeStudentID->m_val.m_nCourseID != argRef.m_nID)
        {
            pNodeStudentID = pNodeStudentID->m_pNext;
        }
        m_treeStudentIDInfo.Delete(pNodeStudentID);
        m_treeCourseIDScore.Delete(pNodeCourseID);
        pNodeCourseID = m_treeCourseIDScore.Find(argRef.m_nID);
    }
}

void Manage::UserInput(int *nInteger)
{
    char szBuf[MAX_SIZE] = "";
    while (scanf("%d", nInteger) != 1)
    {
        gets_s(szBuf, MAX_SIZE);
        printf("�������,��������");
    }
}

Manage::Manage()
{
    StuID tagStudent;
    LessonID tagLesson;
    IDScore tagScore;
    char szInput[MAX_SIZE] = "";
    m_pfName = fopen("Name.txt", "r+");
    m_pfLesson = fopen("Lesson.txt", "r+");
    m_pfIDScore = fopen("IDCourse.txt", "wS+");
    

    SAFE_OPEN(m_pfName);
    SAFE_OPEN(m_pfLesson);
    SAFE_OPEN(m_pfIDScore);
    //��ȡѧ��������ID
    while (fscanf(m_pfName, "%d", &tagStudent.m_nOffest) == 1)
    {
        fscanf(m_pfName, "%d", &tagStudent.m_nID);
        getc(m_pfName);
        Fgets_S(szInput, MAX_SIZE, m_pfName);
        tagStudent.m_strName = szInput;
        InsertStu(tagStudent);
    }
    //��ȡ�γ�����ID
    while (fscanf(m_pfLesson, "%d", &tagLesson.m_nOffest) == 1)
    {
        fscanf(m_pfLesson, "%d", &tagLesson.m_nID);
        getc(m_pfLesson);
        Fgets_S(szInput, MAX_SIZE, m_pfLesson);
        tagLesson.m_strLesson = szInput;
        m_treeCourseNameID.Insert(tagLesson.m_strLesson, tagLesson);
        m_treeIDCourseName.Insert(tagLesson.m_nID, tagLesson);
    }
     MakeLessonRecord();
    rewind(m_pfIDScore);
    //��ȡѡ�μ�¼
    while (fscanf(m_pfIDScore, "%d", &tagScore.m_nOffset) == 1)
    {
        fscanf(m_pfIDScore, "%d", &tagScore.m_nCourseID);
        fscanf(m_pfIDScore, "%d", &tagScore.m_nStuID);
        fscanf(m_pfIDScore, "%d", &tagScore.m_nScore);
        AddCourseRecord(tagScore);
    }
}


Manage::~Manage()
{
    SAFE_PROC(m_pfName);
    SAFE_PROC(m_pfLesson);
}
char* Fgets_S(char *pBuffer, int nMaxCount, FILE *pStream)
{
    char *pRet = nullptr;
    pRet = fgets(pBuffer, nMaxCount, pStream);
    if (pRet != nullptr)
    {
        char *pFind = strchr(pBuffer, '\n');
        if (pFind)
        {
            *pFind = '\0';
        }
    }
    else
    {
         int ch = 0;
         while (getc(pStream) != '\n')
         {
             continue;
         }
    }
    return pRet;
}

