#ifndef AVL_H
#define AVL_H
//#include "BST.cpp"
//#include "AVL.cpp"
#include <memory>
#include <string>
//class AVL;

class AVLNode : public BSTNode
{
    int height;
    friend AVL;
};

class AVL : public BST
{
    //friend BST;
    void Insert(int key);
    std::shared_ptr<AVLNode> leftRotate(std::shared_ptr<AVLNode> lastNode);
    std::shared_ptr<AVLNode> rightRotate(std::shared_ptr<AVLNode> lastNode);
    private:
    std::shared_ptr<AVLNode> root_;
};



#endif // AVL_H_INCLUDED
