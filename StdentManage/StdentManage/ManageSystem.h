#pragma once
#include <iostream>
#include "Mystl.h"
#include "MyTree.h"
using namespace std;


class Manage
{
public:
public:
    Manage();
    ~Manage();
    struct StuID
    {
        StuID() = default;
        int m_nOffest;
        int m_nID;
        CMyString m_strName;
    };

    struct LessonID
    {
        int m_nOffest;
        int m_nID;
        CMyString m_strLesson;
    };
   
    struct IDScore {
        int m_nOffset;
        int m_nCourseID;
        int m_nStuID;
        int m_nScore;
    };

    CMyTree<int, LessonID> m_treeIDCourseName;
    CMyTree<CMyString, LessonID> m_treeCourseNameID;
    CMyTree<CMyString, StuID> m_treeStudentNameID;
    CMyTree<int, StuID> m_treeIDStudentName;
    CMyTree<int, IDScore> m_treeCourseIDScore;
    CMyTree<int, IDScore>  m_treeStudentIDInfo;
    FILE *m_pfName;
    FILE *m_pfLesson;
    FILE *m_pfIDScore;



    void InsertStu(StuID &ref);
    void PrintStu();
    int Menu();
    //����ѧ������
    void FindStudentName();
    //����ѧ��ID
    void FindStudentID(); 
    //���ҿγ���
    void FindLessonName();
    //���ҿγ�ID
    void FindLessonID();
    //����ѡ�޸ÿε�ѧ���Լ��ɼ�
    void FindStudentScore();
    //����ѧ��ѡ����Ϣ
    void FindStudentInfo();
    //����ѧ��
    void AddStudent();
    //�����γ�
    void AddCourse();
    //����ѡ�μ�¼
    void AddCourseRecord();
    //ɾ��ѧ��
    void DelStudent();
    //ɾ���γ�
    void DelCourse();
    //ɾ����¼
    void DelRecord();



    //********************************
     void Start();
    
   
//�������ѡ�μ�¼
    void MakeLessonRecord();
private:
    //����ѡ�μ�¼
    void AddCourseRecord(IDScore &ref);
    
    //ID����ѧ������
    const char* FindStudentName(int nStudentID);
    //ID���ҿγ���
    const char* FindCourseName(int nCourseID);
    //ɾ��ѧ��
    void DelStudentRecord(StuID &argRef);
    //ɾ���γ�
    void DelLessonRecord(LessonID &argRef);
    //�û�����
    void UserInput(int *nInteger);

}; 

