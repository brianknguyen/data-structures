#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#include "AVLL.h"
//#include "json.hpp"




void AVL::Insert(int key)
{
    if (root_ == nullptr) {
		root_ = std::make_shared<AVLNode>(key);
		size_++;
		root_->height = 0;
		return;
	}

    std::shared_ptr<AVLNode> currentNode = root_, lastNode = nullptr;
	while (currentNode != nullptr) {
		lastNode = currentNode;
		currentNode = (key < currentNode->key) ?
			currentNode->left_ : currentNode->right_;
	}
	if (key < lastNode->key) {
		lastNode->left_ = std::make_shared<AVLNode>(key, lastNode);
		lastNode->left_->height = 0;
	//	lastNode->height = 1 + std::max(lastNode->left_->height, lastNode->right->height);

	} else {
		lastNode->right_ = std::make_shared<AVLNode>(key, lastNode);
        lastNode->right_->height = 0;
	}
    lastNode->height = 1 + std::max(lastNode->left_->height, lastNode->right->height);
    int balance = lastNode->left_->height - lastNode->right_->height;
     // Left Left Case
    if (balance > 1 && key < lastNode->left->key)
        root_ = rightRotate(lastNode);

    // Right Right Case
    if (balance < -1 && key > lastNode->right->key)
        root_ = leftRotate(lastNode);

    // Left Right Case
    if (balance > 1 && key > lastNode->left->key)
    {
        node->left =  leftRotate(lastNode->left);
        root_ = rightRotate(lastNode);
    }

    // Right Left Case
    if (balance < -1 && key < lastNode->right->key)
    {
        node->right = rightRotate(lastNode->right);
        root_ = leftRotate(lastNode);
    }
	size_++;
}


std::shared_ptr<AVLNode> AVL::rightRotate(std::shared_ptr<AVLNode> lastNode)
{
    sstd::shared_ptr<AVLNode> x = lastNode->left_;
    sstd::shared_ptr<AVLNode> T2 = x->right_;

    // Perform rotation
    x->right_ = lastNode;
    lastNode->left_ = T2;

    // Update heights
    lastNode->height = max(lastNode->left_->height, lastNode->right_->height)+1;
    x->height = max(x->left_->height, x->right_->height) +1;

    // Return new root
    return x;
}
std::shared_ptr<AVLNode> leftRotate(std::shared_ptr<AVLNode> lastNode)
{
    std::shared_ptr<AVLNode> y = lastNode->right_;
    std::shared_ptr<AVLNode> T2 = y->left_;

    // Perform rotation
    y->left_ = lastNode;
    x->right_ = T2;

    //  Update heights
    x->height = max(x->left_->height, x->right_->height)+1;
    y->height = max(y->left_->height, y->right_->height)+1;

    // Return new root
    return y;
}





