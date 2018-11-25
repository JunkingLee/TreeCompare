//
// Created by Administrator on 2018/11/24.
//

#include "../inc/TreeNode.h"

TreeNode::TreeNode(string strNode, bool bRoot):m_bRoot(bRoot),m_strNode(strNode),m_pParent(NULL) {
}

TreeNode::~TreeNode() {
    m_mNonNormalNode.clear();
    //释放子节点
    int size=m_vChilds.size();
    for(int i=0;i<size;++i)
    {
        delete m_vChilds[i];
    }
}
//根32
//320501,32050101
//320501,32050102
//3205,320501
//32,3205
bool TreeNode::AddChild(string strParent, TreeNode *&pNode) {

    //1：先从非正常挂载节点中查找
    //1.1 判断父节点是否在非正常挂载节点列表中
    map<string,TreeNode*>::iterator it=m_mNonNormalNode.find(strParent);
    if(it!=m_mNonNormalNode.end())
    {
        TreeNode* pNonNormalNode=it->second;
        pNonNormalNode->m_vChilds.push_back(pNode);
        pNode->m_pParent=pNonNormalNode;
        m_mAllNode.insert(pair<string,TreeNode*>(pNode->m_strNode,pNode));
        return true;
    }
    //1.2 判断节点是否在非正常挂载节点列表中
    it=m_mNonNormalNode.find(pNode->m_strNode);
    if(it!=m_mNonNormalNode.end())
    {
        //判断strParent是否存在在树中。
        TreeNode* pFindNode=HasNode(strParent);     //32
        TreeNode* pNonNormalNode=it->second;    //3205
        pNode->Merge(pNonNormalNode);   //3205下子节点合并
        if(pFindNode)   //父节点已经存在
        {
            //将非正常挂载的节点 重新建立挂载关系
            pFindNode->m_vChilds.push_back(pNode);
            pNode->m_pParent=pFindNode;
            delete pNonNormalNode;
            pNonNormalNode=NULL;
            m_mNonNormalNode.erase(it);

        }
        else
        {   //父节点不存在
            delete pNonNormalNode;
            pNonNormalNode=NULL;
            m_mNonNormalNode.erase(it);
            NewNonNormalParentNode(strParent,pNode);
        }
        m_mAllNode.insert(pair<string,TreeNode*>(pNode->m_strNode,pNode));
        return true;
    }

    it=m_mNonNormalNode.begin();
    for(;it!=m_mNonNormalNode.end();++it)
    {
        TreeNode* pNonNormalNode=it->second;
        TreeNode* pNonNormalNodeChild=pNonNormalNode->HasNode(strParent);
        if(pNonNormalNodeChild)
        {
            pNonNormalNodeChild->m_vChilds.push_back(pNode);
            pNode->m_pParent=pNonNormalNodeChild;
            m_mAllNode.insert(pair<string,TreeNode*>(pNode->m_strNode,pNode));
            return true;
        }
    }
    //当前需要添加的子节点，是挂载本节点下的
    if(m_strNode==strParent)
    {
        pNode->m_pParent=this;
        m_vChilds.push_back(pNode);
        m_mAllNode.insert(pair<string,TreeNode*>(pNode->m_strNode,pNode));
        return true;
    }
    else
    {
        TreeNode* pChildNode=HasNode(strParent);
        if(pChildNode)
        {
            pChildNode->m_vChilds.push_back(pNode);
            pNode->m_pParent=pChildNode;
            m_mAllNode.insert(pair<string,TreeNode*>(pNode->m_strNode,pNode));
            return true;
        }
    }

    //未找到父节点,也没有在非正常挂载节点下找到
    //新建父节点，临时存放在非正常挂载节点下
    if(m_bRoot)
    {
        //新建父节点挂载到根目录
        NewNonNormalParentNode(strParent,pNode);
        m_mAllNode.insert(pair<string,TreeNode*>(pNode->m_strNode,pNode));
        return true;
    }
    return false;
}

void TreeNode::NewNonNormalParentNode(string strParent,TreeNode*& pNode) {
    TreeNode* pTreeNode=new TreeNode(strParent);
    pTreeNode->m_pParent=this;
//        this->m_vChilds.push_back(pTreeNode);

    //将子节点挂载到新建的父节点下
    pTreeNode->m_vChilds.push_back(pNode);
    pNode->m_pParent=pTreeNode;

    m_mNonNormalNode.insert(pair<string,TreeNode*>(strParent,pTreeNode));
    m_mAllNode.insert(pair<string,TreeNode*>(pTreeNode->m_strNode,pTreeNode));
}

void TreeNode::Print(int nLevel) {
    for(int i=0;i<nLevel;++i)
    {
        printf(" ");
    }
    printf("%s\n",m_strNode.c_str());
    int size=m_vChilds.size();
    for(int i=0;i<size;++i)
    {
        TreeNode* pNode=m_vChilds[i];
        pNode->Print(nLevel+1);
    }
}

TreeNode *TreeNode::HasNode(string strNode) {
    if(strNode == m_strNode)
    {
        return this;
    }
    else
    {
        int size=m_vChilds.size();
        for(int i=0;i<size;++i)
        {
            TreeNode* pNode=m_vChilds[i];
            TreeNode* pFindNode=pNode->HasNode(strNode);
            if(pFindNode)
            {
                return pFindNode;
            }
        }
    }
    return nullptr;
}

void TreeNode::Shape() {

}

void TreeNode::PrintNonNormal() {
    map<string,TreeNode*>::const_iterator it=m_mNonNormalNode.begin();
    for(it;it!=m_mNonNormalNode.end();++it)
    {
        TreeNode* pNode=it->second;
        pNode->Print();
    }
}

void TreeNode::Merge(TreeNode *&pNode) {
    vector<TreeNode*>::iterator it=pNode->m_vChilds.begin();
    for(;it!=pNode->m_vChilds.end();++it)
    {
        TreeNode* pTreeNode=*it;
        pTreeNode->m_pParent=this;
        m_vChilds.push_back(*it);
    }
    pNode->m_vChilds.clear();
}

void TreeNode::End() {
    map<string,TreeNode*>::iterator it=m_mNonNormalNode.begin();
    for(;it!=m_mNonNormalNode.end();++it)
    {
        TreeNode* pNode=it->second;

    }
}


