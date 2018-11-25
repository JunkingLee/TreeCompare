#include <iostream>
#include "inc/TreeNode.h"

int main() {
    TreeNode *pRoot=new TreeNode("32",true);
    {
        TreeNode *pNode =new TreeNode("32050101");
        pRoot->AddChild("320501",pNode);
    }
    {
        TreeNode *pNode =new TreeNode("3205010101");
        pRoot->AddChild("32050101",pNode);
    }
//    {
//        TreeNode *pNode =new TreeNode("32050102");
//        pRoot->AddChild("320501",pNode);
//    }
    {
        TreeNode *pNode =new TreeNode("320501");
        pRoot->AddChild("3205",pNode);
    }
    {
        TreeNode *pNode =new TreeNode("3205");
        pRoot->AddChild("32",pNode);
    }
//    {
//        TreeNode *pNode =new TreeNode("3205010201");
//        pRoot->AddChild("32050102",pNode);
//    }

    pRoot->Print();
    pRoot->PrintNonNormal();
    delete pRoot;
    pRoot=NULL;
    return 0;
}