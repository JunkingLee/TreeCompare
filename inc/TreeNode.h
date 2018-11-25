//
// Created by Administrator on 2018/11/24.
//

#ifndef TREECOMPARE_TREENODE_H
#define TREECOMPARE_TREENODE_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
using  namespace std;
/**
 * 树结构
 * 支持随机插入树枝，支持调整树结构
 * 暂不知嫁接功能
 * tips:调整树结构后无法支持随机插入树枝
 */
class TreeNode {
public:
    TreeNode(string strNode,bool bRoot=false);

    virtual ~TreeNode();
    //根据父节点添加，若找不到父节点会自动添加父节点在根节点下
    bool AddChild(string strParent,TreeNode*& pNode);

    TreeNode*  HasNode(string strNode);
    //打印树形结构
    void Print(int nLevel=0);

    void PrintNonNormal();
    //树整形
    void Shape();
    //重载赋值操作符，只传递子节点
    TreeNode& operator =(const TreeNode& node)
    {
        if(this != &node )
        {
            this->m_strNode=node.m_strNode;
            this->m_vChilds.assign(node.m_vChilds.begin(),node.m_vChilds.end());
        }
        return *this;
    }
    //调整生产最终树
    void End();
private:
    void NewNonNormalParentNode(string strParent,TreeNode*& pNode);
    //合并
    void Merge(TreeNode*& pNode);
private:
    vector<TreeNode*>   m_vChilds;  //子节点数组
    TreeNode*   m_pParent;  //父节点
    string  m_strNode;  //节点名称
    bool    m_bRoot;    //当前节点是否是根节点
    map<string,TreeNode*> m_mNonNormalNode;
    map<string,TreeNode*> m_mAllNode;
};


#endif //TREECOMPARE_TREENODE_H
