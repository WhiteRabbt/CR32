#pragma once
#include <assert.h>
#include <memory>

template <typename> class Mystack;
template <typename> class Myqueue;
template<typename T>
class CMyList
{

private:
    struct CMyNode {
        CMyNode() = default;
        ~CMyNode()
        {
        }
        CMyNode(T data) {
            m_data = data;
            m_pNext = nullptr;
            m_pPre = nullptr;
        }

        CMyNode* m_pNext;
        CMyNode* m_pPre;
        T m_data;
    };

public:
    //迭代器类
    class iterator {
    public:
        iterator(CMyNode  *p) {
            m_ptr = p;
        }
        bool operator==(iterator &obj) {
            return m_ptr == obj.m_ptr;
        }
        bool operator!=(iterator &obj) {
            return m_ptr != obj.m_ptr;
        }
        T& operator*() {
            return m_ptr->m_data;
        }
        T* operator->() {
            return &m_ptr->m_data;
        }
        iterator& operator++() {
            //++i;
            m_ptr = m_ptr->m_pNext;
            return (*this);
        }
        iterator& operator--() {
            //--i;
            m_ptr = m_ptr->m_pPre;
            return (*this);
        }
    private:
        CMyNode *m_ptr;
        friend CMyList;
    };
    //****************************
public:
    CMyList();
    ~CMyList();

    void push_back(const T& n);
    void push_front(const T& n);
    void pop_front();
    void pop_back();
    iterator insert(iterator position, const T& val);
    iterator begin();
    iterator end();
    bool empty() const;
    int size() const;
    T &front();
    T & back();
    iterator erase(iterator position);
private:
     CMyNode* m_pHead; //表示头结点
    int m_nSize;
};
//***********************************************************
template<typename T>
CMyList<T>::CMyList() {
    m_pHead = new CMyNode;
    m_pHead->m_pNext = m_pHead;
    m_pHead->m_pPre = m_pHead;
    m_nSize = 0;
}template<typename T>
CMyList<T>::~CMyList()
{
    CMyNode *pTemp = m_pHead;
    for (int i = 0; i < size() + 1 && pTemp != nullptr; i++)
    {
        m_pHead = m_pHead->m_pNext;
        delete pTemp;
        pTemp = m_pHead;
    }


}

//“哨兵”

//llvm, ollvm
template<typename T>
void CMyList<T>::push_back(const T & n) {

    CMyNode* pEnd = new CMyNode(n);

    //重置末尾结点
    pEnd->m_pPre = m_pHead->m_pPre;
    pEnd->m_pNext = m_pHead;
    m_pHead->m_pPre->m_pNext = pEnd;
    //重置头指针
    m_pHead->m_pPre = pEnd;

    m_nSize++;
    return;
}
template<typename T>
void CMyList<T>::push_front(const T & n) {

    CMyNode* pNew = new CMyNode(n);
    CMyNode* pNext = m_pHead->m_pNext;

    m_pHead->m_pNext = pNew;
    //链接新分配结点
    pNew->m_pPre = m_pHead;
    pNew->m_pNext = pNext;

    pNext->m_pPre = pNew;

    m_nSize++;
}
template<typename T>
void CMyList<T>::pop_front()
{
    assert(m_nSize >= 1);
    CMyNode *pTemp = m_pHead->m_pNext;
    CMyNode *pFirst = pTemp->m_pNext;
    m_pHead->m_pNext = pFirst;
    pFirst->m_pPre = m_pHead;
    delete pTemp;

    m_nSize--;
}
template<typename T>
void CMyList<T>::pop_back()
{
    assert(m_nSize >= 1);

    CMyNode *pTemp = m_pHead->m_pPre;
    CMyNode *pEnd = pTemp->m_pPre;
    m_pHead->m_pPre = pEnd;
    pEnd->m_pNext = m_pHead;
    delete pTemp;

    m_nSize--;
}
template<typename T>
typename CMyList<T>::iterator CMyList<T>::insert(iterator position, const T & val)
{
    CMyNode* pNew = new CMyNode(val);

    CMyNode *pPre = position.m_ptr->m_pPre;
    pPre->m_pNext = pNew;
    position.m_ptr->m_pPre = pNew;
    pNew->m_pNext = position.m_ptr;
    pNew->m_pPre = pPre;

    m_nSize++;
    return iterator(pNew);
}

template<typename T>
typename CMyList<T>::iterator CMyList<T>::begin() {
    return iterator(m_pHead->m_pNext);
}


template<typename T>
typename CMyList<T>::iterator CMyList<T>::end()
{
    return iterator(m_pHead);
}
template<typename T>
bool CMyList<T>::empty() const
{
    return m_nSize == 0;
}
template<typename T>
int CMyList<T>::size() const
{
    return m_nSize;
}
template<typename T>
T & CMyList<T>::front()
{
    return m_pHead->m_pNext->m_data;
}
template<typename T>
T & CMyList<T>::back()
{
    return m_pHead->m_pPre->m_data;
    // TODO: 在此处插入 return 语句
}
//    head    1    2    
//    head    1
template<typename T>
typename CMyList<T>::iterator CMyList<T>::erase(iterator position)
{
    assert(m_nSize >= 1 && position != end());

    CMyNode *pTemp = position.m_ptr;
    CMyNode *pPre = pTemp->m_pPre;
    CMyNode *pNext = pTemp->m_pNext;
    pPre->m_pNext = pNext;
    pNext->m_pPre = pPre;
    delete pTemp;
    m_nSize--;
    return iterator(pNext);
}

template<typename T>
class Myqueue : private CMyList<T> {

public:
    void pop();

    T& front();

    T& back();

    void push(T nT);

    int size()
    {
        return CMyList<T>::size();
    }

    bool empty()
    {
        return CMyList<T>::empty();
    }
};

template<typename T>
void  Myqueue<T>::pop()
{
    CMyList<T>::pop_front();
}

template<typename T>
inline T& Myqueue<T>::front()
{
    return CMyList<T>::front();
}

template<typename T>
inline T & Myqueue<T>::back()
{
    return CMyList<T>::push_back();
}

template<typename T>
inline void Myqueue<T>::push(T nT)
{
    CMyList<T>::push_front(nT);
}
//我的栈
template<typename T>
class Mystack : private CMyList<T> {
public:
    Mystack() = default;
    T& top()
    {
        return CMyList<T>::front();
    }

    bool empty()
    {
        return CMyList<T>::empty();
    }
    int size()
    {
        return CMyList<T>::size();
    }

    void push(const T& tRef)
    {
        return CMyList<T>::push_front(tRef);
    }
    void pop()
    {
        return CMyList<T>::pop_front();
    }
};
//CMyString
#define SIZE 16

class CMyString
{
public:
    CMyString() :m_nSize(0), m_nCapacity(0), m_ptr(0) {}
    CMyString(const CMyString &str)
    {
        m_nSize = str.size();
        m_nCapacity = str.m_nCapacity;
        m_ptr = new char[m_nCapacity + 1];
        strcpy(m_ptr, str.c_str());
    }
    CMyString(const char *pSource)
    {
        m_nSize = strlen(pSource);
        m_nCapacity = (m_nSize / SIZE + 1) * 16 - 1;
        m_ptr = new char[m_nCapacity + 1];
        strcpy(m_ptr, pSource);
    }
    ~CMyString()
    {
        if (m_ptr != nullptr)
        {
            delete[]m_ptr;
        }
    }

    //赋值
    CMyString& operator=(const char *pSource)
    {
        int nSize = strlen(pSource);
        if (m_nCapacity >= nSize)
        {
            strcpy(m_ptr, pSource);
            m_nSize = nSize;
        }
        else
        {
            m_nSize = strlen(pSource);
            m_nCapacity = (m_nSize / SIZE + 1) * 16 - 1;
            delete[]m_ptr;
            m_ptr = new char[m_nCapacity + 1];
            strcpy(m_ptr, pSource);
        }
        return *this;
    }

    //返回大小
    int size()const
    {
        return m_nSize;
    }

    //返回内置指针
    const char* c_str()const
    {
        return m_ptr;
    }
    //<
    bool operator<(const CMyString &str) const
    {
        if (strcmp(m_ptr, str.c_str()) < 0)
        {
            return true;
        }
        return false;
    }

    //>
    bool operator>(const CMyString &str) const
    {
        if (strcmp(m_ptr, str.c_str()) > 0)
        {
            return true;
        }
        return false;
    }

    //=
    CMyString& operator=(const CMyString &str)
    {
        if (this == &str)
        {
            return *this;
        }
        delete[]m_ptr;
        m_nSize = str.size();
        m_nCapacity = str.m_nCapacity;
        m_ptr = new char[m_nCapacity + 1];
        strcpy(m_ptr, str.c_str());
        return *this;

    }

    //+
    CMyString operator+(const CMyString &str)
    {
        char *pStr = new char[m_nSize + str.m_nSize + 1];
        strcpy(pStr, m_ptr);
        strcat(pStr, str.c_str());
        CMyString newString(pStr);
        delete[]pStr;
        return newString;
    }

private:
    int m_nSize;
    int m_nCapacity;
    char *m_ptr;
};



