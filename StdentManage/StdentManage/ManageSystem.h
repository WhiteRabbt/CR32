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
    //查找学生姓名
    void FindStudentName();
    //查找学生ID
    void FindStudentID(); 
    //查找课程名
    void FindLessonName();
    //查找课程ID
    void FindLessonID();
    //查找选修该课的学生以及成绩
    void FindStudentScore();
    //查找学生选课信息
    void FindStudentInfo();
    //新增学生
    void AddStudent();
    //新增课程
    void AddCourse();
    //增加选课记录
    void AddCourseRecord();
    //删除学生
    void DelStudent();
    //删除课程
    void DelCourse();
    //删除记录
    void DelRecord();



    //********************************
     void Start();
    
   
//生成随机选课记录
    void MakeLessonRecord();
private:
    //新增选课记录
    void AddCourseRecord(IDScore &ref);
    
    //ID查找学生姓名
    const char* FindStudentName(int nStudentID);
    //ID查找课程名
    const char* FindCourseName(int nCourseID);
    //删除学生
    void DelStudentRecord(StuID &argRef);
    //删除课程
    void DelLessonRecord(LessonID &argRef);
    //用户输入
    void UserInput(int *nInteger);

}; 

