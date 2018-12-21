#pragma once
#include <assert.h>

template<typename T>
class CMyList
{

private:
    struct CMyNode {
        CMyNode() = default;
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

    void reverse();



private:
    CMyNode* m_pHead; //表示头结点
    int m_nSize;
};

template<typename T>
CMyList<T>::CMyList() {
    m_pHead = new CMyNode;
    m_pHead->m_pNext = m_pHead;
    m_pHead->m_pPre = m_pHead;
    m_nSize = 0;
}template<typename T>
CMyList<T>::~CMyList()
{
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
    return m_pHead->m_data;
    // TODO: 在此处插入 return 语句
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
class MyStack : private CMyList<T> {

public:
    void push(const T &obj)
    {
        CMyList<T>::push_back(obj);
    }
    int size() {
        return  CMyList<T>::size();
    }
    void pop() {
        CMyList<T>::pop_back();
    }
    int top() {
        return CMyList<T>::back();
    }
    bool empty() {
        return CMyList<T>::empty();
    }

};

