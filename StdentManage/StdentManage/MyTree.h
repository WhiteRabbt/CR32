#pragma once
#include "MyTree.h"
#include "Mystl.h"
#include <algorithm>

//二叉排序树
/*
        50
      45  55

*/
template<typename KEY, typename VAL>
class CMyTree
{
public:
    struct CMyTreeNode {
        CMyTreeNode(KEY key, VAL val) {
            m_pParent = nullptr;
            m_pLeft = nullptr;
            m_pRight = nullptr;
            m_pNext = nullptr;
            m_nHeight = 1;
            m_val = val;
            m_key = key;
        }
        //CMyTreeNode Data member
        VAL m_val;
        KEY m_key;
        int m_nHeight;
        CMyTreeNode* m_pParent;
        CMyTreeNode* m_pLeft;
        CMyTreeNode* m_pRight;
        CMyTreeNode* m_pNext;
    };
    class iterator {
    public:
        iterator(CMyTreeNode  *pNode) {
            m_pNodeCur = pNode;
        }
        bool operator==(iterator &iterObj) {
            return m_pNodeCur == iterObj.m_pNodeCur;
        }
        bool operator!=(iterator &iterObj) {
            return m_pNodeCur != iterObj.m_pNodeCur;
        }
        VAL& operator*() {
            return m_pNodeCur->m_val;
        }
        VAL* operator->() {
            return &m_pNodeCur->m_val;
        }
        iterator& operator++() {
            if ((m_pNodeCur->m_pParent == nullptr) && (m_pNodeCur->m_pRight == nullptr))
            {
                m_pNodeCur = nullptr;
            }
            else if (m_pNodeCur->m_pRight != nullptr)
            {
                m_pNodeCur = m_pNodeCur->m_pRight;
                while (m_pNodeCur->m_pLeft)
                {
                    m_pNodeCur = m_pNodeCur->m_pLeft;
                }
            }
            else
            {
                CMyTreeNode *pNodeBig = m_pNodeCur;
                while (pNodeBig->m_pParent != nullptr)
                {
                    pNodeBig = pNodeBig->m_pParent;
                }
                while (pNodeBig->m_pRight != nullptr)
                {
                    pNodeBig = pNodeBig->m_pRight;
                }
                if (pNodeBig == m_pNodeCur)
                {
                    m_pNodeCur = nullptr;
                    return (*this);
                }
                CMyTreeNode *pParent = m_pNodeCur->m_pParent;
                while (m_pNodeCur == pParent->m_pRight)
                {
                    m_pNodeCur = pParent;
                    pParent = pParent->m_pParent;
                }
                m_pNodeCur = pParent;
            }
            return (*this);
        }
    private:
        CMyTreeNode *m_pNodeCur;
        friend CMyTree;
    };

public:
    CMyTree();
    ~CMyTree();

    /*
            A
        B       C
      D      F    G

    A B D E C F G
    A B C D ? F G

    */
    //Begin
    iterator begin();

    //End()
    iterator end();

    //[]
    VAL& operator[](KEY key)
    {
        auto pRet = Find(key);
        if (pRet != nullptr)
        {
            return pRet->m_val;
        }
        return VAL();
    }

    //增
    void Insert(KEY key, VAL val);

    //删
    bool Delete(KEY key);
    bool Delete(CMyTreeNode* pNode);

    //改
    bool ReSet(KEY key, VAL val, KEY keyChange);

    //右旋转
    void RotateRight(CMyTreeNode * pK1, CMyTreeNode *pK2);

    //左旋转
    void RotateLeft(CMyTreeNode * pK1, CMyTreeNode *pK2);

    //调整
    void Adjust(CMyTreeNode *pNode);

    int GetHeight(CMyTreeNode *pNode);

    //查
    CMyTreeNode* Find(KEY key);

    CMyTreeNode* GetRoot() {
        return m_pRoot;
    }

    //释放所有节点
    void FreeTree(CMyTreeNode *pNode);

private:
    CMyTreeNode* m_pRoot;
    int m_nSize;//表示节点的总个数
};

template<typename KEY, typename VAL>
CMyTree<KEY, VAL>::CMyTree() {

    m_pRoot = nullptr;
    m_nSize = 0;
}

template<typename KEY, typename VAL>
CMyTree<KEY, VAL>::~CMyTree()
{
    FreeTree(m_pRoot);
}

/*
        50
      45  55
*/

template<typename KEY, typename VAL>
typename CMyTree<KEY, VAL>::iterator  CMyTree<KEY, VAL>::begin()
{
    CMyTreeNode *pNodeRet = m_pRoot;
    while (pNodeRet->m_pLeft != nullptr)
    {
        pNodeRet = pNodeRet->m_pLeft;
    }
    return iterator(pNodeRet);
}

template<typename KEY, typename VAL>
typename CMyTree<KEY, VAL>::iterator  CMyTree<KEY, VAL>::end()
{
    return iterator(nullptr);
}

template<typename KEY, typename VAL>
void CMyTree<KEY, VAL>::Insert(KEY key, VAL val) {
    CMyTreeNode* pNew = new CMyTreeNode(key, val);

    if (m_nSize == 0) {
        m_pRoot = pNew;
        m_nSize++;
        return;
    }

    CMyTreeNode* pCurNode = m_pRoot;

    //表示往左边插入数据
    while (true) {

        if (pCurNode->m_key > key) {
            //选择左边
            if (pCurNode->m_pLeft == nullptr) {
                pCurNode->m_pLeft = pNew;
                pNew->m_pParent = pCurNode;
                break;
            }
            else {
                pCurNode = pCurNode->m_pLeft;
            }

        }
        else if (pCurNode->m_key < key) {
            //选择右边
            if (pCurNode->m_pRight == nullptr) {
                pCurNode->m_pRight = pNew;
                pNew->m_pParent = pCurNode;
                break;
            }
            else {
                pCurNode = pCurNode->m_pRight;
            }
        }
        else {
            //表示等于
            while (pCurNode->m_pNext != nullptr)
            {
                pCurNode = pCurNode->m_pNext;
            }
            pCurNode->m_pNext = pNew;
            pNew->m_pParent = pCurNode;
            pNew->m_pRight = pCurNode->m_pRight;
            pNew->m_pLeft = pCurNode->m_pLeft;
            pNew->m_key = pCurNode->m_key;
            pNew->m_nHeight = pCurNode->m_nHeight;
            m_nSize++;
            return;
        }
    }
    Adjust(pCurNode);
    m_nSize++;
    return;
}

template<typename KEY, typename VAL>
bool CMyTree<KEY, VAL>::Delete(KEY key)
{
    CMyTreeNode * pFind = Find(key);
    if (pFind == nullptr) {
        return false;
    }
    Delete(pFind);

    return true;
}


/*
          50
      45      75
    30    55       80
        53  60  78    90
                  79
          50
            75
          55


*/
//VAL m_val;
//KEY m_key;
//int m_nHeight;
//CMyTreeNode* m_pParent;
//CMyTreeNode* m_pLeft;
//CMyTreeNode* m_pRight;
//CMyTreeNode* m_pNext;
template<typename KEY, typename VAL>
bool CMyTree<KEY, VAL>::Delete(CMyTreeNode * pNode)
{

    //删除根节点链表首结点
    if (pNode->m_pNext != nullptr && pNode->m_pParent == nullptr)
    {
        auto pNodeRoot = pNode->m_pNext;
        pNodeRoot->m_pParent = nullptr;
        m_pRoot = pNodeRoot;
        delete pNode;
        m_nSize--;
        return true;
    }
    //普通链表根节点
    else if (pNode->m_pParent != nullptr && pNode != pNode->m_pParent->m_pNext && pNode->m_pNext != nullptr)
    {
        auto pParent = pNode->m_pParent;
        auto *pNodeSecond = pNode->m_pNext;

        if (pParent->m_pLeft == pNode)
        {
            pParent->m_pLeft = pNodeSecond;
        }
        else
        {
            pParent->m_pRight = pNodeSecond;
        }
        pNodeSecond->m_pParent = pParent;
        delete pNode;
        m_nSize--;
        return true;
    }
    //删除链表中最后一项
    else if (pNode->m_pNext == nullptr && pNode->m_pParent->m_pNext == pNode)
    {
        pNode->m_pParent->m_pNext = nullptr;
        delete pNode;
        m_nSize--;
        return true;
    }
    //如果删除节点为链表中某一项
    else if (pNode->m_pNext != nullptr)
    {
        auto pParent = pNode->m_pParent;
        auto *pNodeSecond = pNode->m_pNext;

        pParent->m_pNext = pNodeSecond;
        pNodeSecond->m_pParent = pParent;
        delete pNode;
        m_nSize--;
        return true;
    }



    if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr) {
        //没有儿子
        if (pNode->m_pParent == nullptr) {
            m_pRoot = nullptr;
        }
        else {
            if (pNode->m_pParent->m_pLeft == pNode) {
                pNode->m_pParent->m_pLeft = nullptr;
            }
            else {
                pNode->m_pParent->m_pRight = nullptr;
            }
        }
    }
    else if (pNode->m_pLeft != nullptr && pNode->m_pRight != nullptr) {
        //有两儿子
        CMyTreeNode* pCur = pNode->m_pRight;
        while (pCur->m_pLeft != nullptr) {
            pCur = pCur->m_pLeft;
        }

        pNode->m_val = pCur->m_val;
        pNode->m_key = pCur->m_key;
        pNode->m_pNext = pCur->m_pNext;

        if (pCur->m_pNext != nullptr)
        {
            pCur->m_pNext->m_pParent = pNode;
        }
        pCur->m_pNext = nullptr;
        Delete(pCur);
        return true;
    }
    else {
        //有一个儿子

        if (pNode->m_pLeft != nullptr) {
            //表示只有左儿子
            if (pNode->m_pParent != nullptr) {
                if (pNode->m_pParent->m_pLeft == pNode) {
                    pNode->m_pParent->m_pLeft = pNode->m_pLeft;
                }
                else {
                    pNode->m_pParent->m_pRight = pNode->m_pLeft;
                }
            }
            else {
                m_pRoot = pNode->m_pLeft;
            }

            pNode->m_pLeft->m_pParent = pNode->m_pParent;

        }
        else {
            if (pNode->m_pParent != nullptr) {
                //表示只有右儿子
                if (pNode->m_pParent->m_pLeft == pNode) {
                    pNode->m_pParent->m_pLeft = pNode->m_pRight;
                }
                else {
                    pNode->m_pParent->m_pRight = pNode->m_pRight;
                }
            }
            else {
                m_pRoot = pNode->m_pRight;
            }

            pNode->m_pRight->m_pParent = pNode->m_pParent;
        }
    }

    Adjust(pNode->m_pParent);
    delete pNode;
    m_nSize--;

    return true;
}

template<typename KEY, typename VAL>
bool CMyTree<KEY, VAL>::ReSet(KEY key, VAL val, KEY keyChange)
{
    CMyTreeNode* pFindNode = nullptr;

    pFindNode = Find(keyChange);
    if (pFindNode)
    {
        Delete(pFindNode);
        Insert(key, val);
        return true;
    }
    return false;
}

/*
    pg                                                  pg
        pk1                                                Pk2
      A     pk2          ==>                             Pk1   C
          B     C                                      A    B
*/
template<typename KEY, typename VAL>
void CMyTree<KEY, VAL>::RotateLeft(CMyTreeNode * pK1, CMyTreeNode *pK2)
{
    CMyTreeNode * pG = pK1->m_pParent;
    CMyTreeNode * pA = pK1->m_pLeft;
    CMyTreeNode * pB = pK2->m_pLeft;
    CMyTreeNode * pC = pK2->m_pRight;

    if (pG != nullptr)
    {
        if (pG->m_pLeft == pK1)
        {
            pG->m_pLeft = pK2;
        }
        else
        {
            pG->m_pRight = pK2;
        }
    }
    else
    {
        m_pRoot = pK2;
    }
    pK2->m_pParent = pG;
    pK2->m_pLeft = pK1;
    pK1->m_pParent = pK2;
    pK1->m_pRight = pB;
    if (pB != nullptr)
    {
        pB->m_pParent = pK1;
    }

    pK1->m_nHeight = std::max(GetHeight(pA), GetHeight(pB)) + 1;
    pK2->m_nHeight = std::max(GetHeight(pK1), GetHeight(pC)) + 1;

}
template<typename KEY, typename VAL>
void CMyTree<KEY, VAL>::Adjust(CMyTreeNode * pNode)
{

    CMyTreeNode* pK1 = nullptr;
    CMyTreeNode* pK2 = nullptr;
    CMyTreeNode* pK3 = nullptr;

    while (pNode != nullptr)
    {
        pK1 = pNode;
        pNode->m_nHeight = std::max(GetHeight(pNode->m_pLeft), GetHeight(pNode->m_pRight)) + 1;

        int nSubHeight = GetHeight(pNode->m_pLeft) - GetHeight(pNode->m_pRight);

        if (std::abs(nSubHeight) > 1) {
            if (nSubHeight > 1) {
                pK2 = pK1->m_pLeft;
            }
            else {
                pK2 = pK1->m_pRight;
            }

            if (GetHeight(pK2->m_pLeft) - GetHeight(pK2->m_pRight) > 0) {
                pK3 = pK2->m_pLeft;
            }
            else {
                pK3 = pK2->m_pRight;
            }

            //开始旋转
            //判断4种情况
            //左单旋
            /*
                pK1
                   pK2
                      pK3
            */
            if (pK2 == pK1->m_pRight && pK3 == pK2->m_pRight) {
                RotateLeft(pK1, pK2);
            }


            //右单旋
            /*
                      pK1
                   pK2
                pK3
            */
            if (pK2 == pK1->m_pLeft && pK3 == pK2->m_pLeft) {
                RotateRight(pK1, pK2);
            }

            //右左双旋
            /*
                pK1
                   pK2
                pK3
            */
            if (pK2 == pK1->m_pRight && pK3 == pK2->m_pLeft) {
                RotateRight(pK2, pK3);
                RotateLeft(pK1, pK3);
            }

            //左右双旋
            /*
                pK1
             pK2
                pK3
            */
            if (pK2 == pK1->m_pLeft && pK3 == pK2->m_pRight) {
                RotateLeft(pK2, pK3);
                RotateRight(pK1, pK3);
            }
        }

        pNode = pNode->m_pParent;
    }
}

template<typename KEY, typename VAL>
int CMyTree<KEY, VAL>::GetHeight(CMyTreeNode * pNode)
{
    if (pNode != nullptr)
    {
        return pNode->m_nHeight;
    }
    return 0;
}
/*
   pG                       pG
      pK1                       pK2
   pK2    A        ==>         B    pK1
  B   C                            C    A
*/
template<typename KEY, typename VAL>
void CMyTree<KEY, VAL>::RotateRight(CMyTreeNode * pK1, CMyTreeNode *pK2)
{
    CMyTreeNode* pG = pK1->m_pParent;
    CMyTreeNode* pA = pK1->m_pRight;
    CMyTreeNode* pB = pK2->m_pLeft;
    CMyTreeNode* pC = pK2->m_pRight;

    pK2->m_pParent = pG;
    pK2->m_pRight = pK1;

    pK1->m_pParent = pK2;
    pK1->m_pLeft = pC;

    if (pC != nullptr) {
        pC->m_pParent = pK1;
    }

    if (pG != nullptr) {
        if (pG->m_pLeft == pK1) {
            pG->m_pLeft = pK2;
        }
        else {
            pG->m_pRight = pK2;
        }
    }
    else {
        m_pRoot = pK2;
    }

    //修正pK1和pK2的高度
    pK1->m_nHeight = std::max(GetHeight(pA), GetHeight(pC)) + 1;
    pK2->m_nHeight = std::max(GetHeight(pK1), GetHeight(pB)) + 1;


}

template<typename KEY, typename VAL>
typename CMyTree<KEY, VAL>::CMyTreeNode * CMyTree<KEY, VAL>::Find(KEY key)
{
    CMyTreeNode* pCur = m_pRoot;

    while (pCur != nullptr) {

        if (pCur->m_key > key) {
            pCur = pCur->m_pLeft;
        }
        else if (pCur->m_key < key) {
            pCur = pCur->m_pRight;
        }
        else {
            return pCur;
        }
    }

    return nullptr;
}

template<typename KEY, typename VAL>
void CMyTree<KEY, VAL>::FreeTree(CMyTreeNode * pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    FreeTree(pNode->m_pLeft);
    FreeTree(pNode->m_pRight);
    delete pNode;
    m_nSize--;


}
