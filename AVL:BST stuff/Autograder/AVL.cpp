#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#include "AVL.h"
#include "json.hpp"

AVLNode::AVLNode(int key) :
	key_(key),
	parent_(std::weak_ptr<AVLNode>()),
	left_(nullptr),
	right_(nullptr) {}

AVLNode::AVLNode(int key, std::weak_ptr<AVLNode> parent) :
	key_(key),
	parent_(parent),
	left_(nullptr),
	right_(nullptr) {}

bool AVLNode::IsLeaf() const {
	return left_ == nullptr && right_ == nullptr;
}

bool AVLNode::HasLeftChild() const {
	return left_ != nullptr;
}

bool AVLNode::HasRightChild() const {
	return right_ != nullptr;
}

void AVLNode::DeleteChild(std::shared_ptr<AVLNode> v) {
	if (left_ == v) {
		left_ = nullptr;
	} else if (right_ == v) {
		right_ = nullptr;
	} else {
		std::cerr << "AVLNode::DeleteChild Error: non-child passed as argument\n";
		exit(EXIT_FAILURE);
	}
}

void AVLNode::ReplaceChild(std::shared_ptr<AVLNode> v, std::shared_ptr<AVLNode> u) {
	if (left_ == u || right_ == u) {
		std::cerr << "AVLNode::ReplaceChild Error: child passed as replacement\n";
	}
	if (left_ == v) {
		left_ = u;
		u->parent_ = v->parent_;
	} else if (right_ == v) {
		right_ = u;
		u->parent_ = v->parent_;
	} else {
		std::cerr << "AVLNode::ReplaceChild Error: non-child passed as argument\n";
		exit(EXIT_FAILURE);
	}
}

AVL::AVL() : root_(nullptr), size_(0) {}

void AVL::updateHeight(std::shared_ptr<AVLNode> x)
{
    if (x->HasRightChild() && x->HasLeftChild())
    {

            x->height = std::max(x->left_->height, x->right_->height ) +1;
            x->balance = x->left_->height - x->right_->height ;


    }
    else if (x->HasLeftChild() && !x->HasRightChild())
    {
            x->height = x->left_->height + 1;
            x->balance = x->left_->height + 1;
    }
    else if (x->HasRightChild()&& !x->HasLeftChild())
    {
            x->height = x->right_->height + 1;
            x->balance = -x->right_->height - 1;
    }
    else if (!x->HasRightChild()&& !x->HasLeftChild())
    {
            x->height = 0;
            x->balance = 0;
    }

    return;
}

void AVL::rightright(std::shared_ptr<AVLNode> lastNode){
    bool isroot;

    //uses the implentation code for cases of righright rotation
    if (lastNode == root_)
    {
        isroot = true;
    }
    if (isroot)
    {
        std::shared_ptr<AVLNode> x = lastNode->left_;
        std::shared_ptr<AVLNode> y = x->left_;
        root_ = std::make_shared<AVLNode>(x->key_);
        root_->left_=x->left_;
        root_->right_=x->right_;

        if(root_->HasRightChild())
       {
        lastNode->left_=root_->right_;

        }
        else{
            root_->left_ = nullptr;
        }

        root_->right_ = lastNode;
        lastNode->parent_ = root_;

        updateHeight(lastNode);

        updateHeight(root_);
    }
    else {
        std::shared_ptr<AVLNode> z = lastNode->parent_.lock();
        std::shared_ptr<AVLNode> x = lastNode->left_;
        std::shared_ptr<AVLNode> y = x ->left_;
        //std::cout <<"ran" << std::endl;
        if(x->HasRightChild()){
        lastNode->left_ = x->right_;
         }
         else{
            lastNode->left_ = nullptr;
         }

        x->right_ = lastNode;
        lastNode->parent_ = x;


        if(z->left_ == lastNode)
        {
            z->left_=x;
            x->parent_ =z;
        }
        else
        {
            z->right_=x;
            x->parent_=z;
        }
        updateHeight(lastNode);
        updateHeight(x);
       // std::cout << c->height << std::endl;
       // updateHeight(c);
        //std::cout << c->height << std::endl;

        updateHeight(z);
        std::shared_ptr<AVLNode> p = z->parent_.lock();
        while (p!= nullptr)
        {
            updateHeight(p);
            p = p->parent_.lock();
        }

    }



}


void AVL::leftleft(std::shared_ptr<AVLNode> lastNode){





}

void AVL::rightleft(std::shared_ptr<AVLNode> lastNode) {
  //  std::cout <<"ran" << std::endl;

  //uses right left rotation to blance the desired avl tree.
    bool isroot;
    if (lastNode == root_)
    {
        isroot = true;
    }
    if (isroot)
    {
        std::shared_ptr<AVLNode> x = lastNode->right_;
        std::shared_ptr<AVLNode> y = x->left_;
        root_ = std::make_shared<AVLNode>(y->key_);
        root_->left_=y->left_;
        root_->right_=y->right_;

        lastNode->right_=root_->left_;

        if(root_->HasLeftChild())
        {
            root_->left_->parent_ = lastNode;
        }
        x->left_ = root_->right_;

        if(root_->HasRightChild())
        {
            root_->right_->parent_=x;
        }
        root_->right_ = x;
        x->parent_ = root_;
        updateHeight(lastNode);
        updateHeight(x);
        updateHeight(root_);

    }

    else {
           //     std::cout <<"else" << std::endl;
        std::shared_ptr<AVLNode> z = lastNode->parent_.lock();
        std::shared_ptr<AVLNode> x = lastNode->right_;
        //std::cout <<"ran" << std::endl;

        std::shared_ptr<AVLNode> y = x ->left_;
        //std::cout <<"ran" << std::endl;

        lastNode->right_ = y->left_;

        if(y->HasLeftChild())
        {
            y->left_->parent_ = lastNode;
        }
        x->left_ = y->right_;
        if(y->HasRightChild())
        {
            y->right_->parent_ = x;
        }
        y->left_ =lastNode;
        lastNode->parent_=y;

        y->right_=x;
        x->parent_=y;

        if(z->left_ == lastNode)
        {
            z->left_=y;
            y->parent_ =z;
        }
        else
        {
            z->right_=y;
            y->parent_=z;
        }
        updateHeight(lastNode);
        updateHeight(x);
        updateHeight(y);
        updateHeight(z);

        std::shared_ptr<AVLNode> p = z->parent_.lock();
        while (p!= nullptr)
        {
            updateHeight(p);
            p = p->parent_.lock();
        }


    }

}


void AVL::leftright(std::shared_ptr<AVLNode> lastNode) {



}
void AVL::Insert(int key)
{
    if (root_ == nullptr) {
		root_ = std::make_shared<AVLNode>(key);
		size_++;
		root_->height = 0;
		return;
	}

    std::shared_ptr<AVLNode> currentNode = root_, lastNode = nullptr;
	std::shared_ptr<AVLNode> parent;
    bool leftchild;
	while (currentNode != nullptr) {
		lastNode = currentNode;
		currentNode = (key < currentNode->key_) ?
        currentNode->left_ : currentNode->right_;
	}
	if (key < lastNode->key_) {
        leftchild = true;
		lastNode->left_ = std::make_shared<AVLNode>(key, lastNode);
		lastNode->left_->height = 0;
		lastNode->left_->balance = 0;
	    parent = lastNode->left_->parent_.lock();
		while (parent != nullptr)
        {
            updateHeight(parent);
            parent = parent->parent_.lock();
        }


	} else {
	    leftchild = false;
		lastNode->right_ = std::make_shared<AVLNode>(key, lastNode);
        lastNode->right_->height = 0;
        lastNode->right_->balance = 0;
        parent = lastNode->right_->parent_.lock();
        while (parent != nullptr)
        {
            updateHeight(parent);
            parent = parent->parent_.lock();
        }
	}

    std::shared_ptr<AVLNode> parentbalance;
    std::shared_ptr<AVLNode> tempnode;
    std::shared_ptr<AVLNode> tnode;


    if (leftchild)
    {
        parentbalance = lastNode->left_->parent_.lock();
    }
    else
    {
        parentbalance = lastNode->right_->parent_.lock();
    }


   while (parentbalance != nullptr)
        {

            // Left Right Case
            if (parentbalance->balance > 1){
                if (parentbalance->left_->HasRightChild()){
                    if (parentbalance->left_->balance == -1)
                    {

                          // leftright(parentbalance);
                            break;

                    }
                }
                else
                {
                        rightright(parentbalance);
                        break;
                }
            }

            // Right Left Case
            if (parentbalance->balance < -1){
                if (parentbalance->right_->HasLeftChild())
                {
                    if (parentbalance->right_->balance == 1)
                    {


                      rightleft(parentbalance);
                        break;

                    }
                }
                else {

                   //leftleft(parentbalance);
                    break;
                }
            }
            parentbalance = parentbalance->parent_.lock();

        }

	size_++;
}


bool AVL::Delete(int key) {
	std::shared_ptr<AVLNode> currentNode = root_;
	while (currentNode != nullptr) {
		if (currentNode->key_ == key) {
			if (currentNode->IsLeaf()) {
				DeleteLeaf(currentNode);
			} else if (currentNode->left_ == nullptr) {
				assert(currentNode->right_ != nullptr);
				std::shared_ptr<AVLNode> parent = currentNode->parent_.lock();
				parent->ReplaceChild(currentNode, currentNode->right_);
				size_--; assert(size_ >= 0);
			} else if (currentNode->right_ == nullptr) {
				assert(currentNode->left_ != nullptr);
				std::shared_ptr<AVLNode> parent = currentNode->parent_.lock();
				parent->ReplaceChild(currentNode, currentNode->left_);
				size_--; assert(size_ >= 0);
			} else {
				currentNode->key_ = DeleteMin(currentNode);
			}
		}
		currentNode = (key < currentNode->key_) ?
			currentNode->left_ : currentNode->right_;
	}
	return false;
}

int AVL::DeleteMin() {
	return DeleteMin(root_);
}


void AVL::DeleteLeaf(std::shared_ptr<AVLNode> currentNode) {
	std::shared_ptr<AVLNode> parent = currentNode->parent_.lock();
	if (parent == nullptr) {
		// Delete root
		root_ = nullptr;
		size_--; assert(size_ == 0);
	} else {
		if (parent->right_ == currentNode) {
			parent->right_ = nullptr;
		} else if (parent->left_ == currentNode) {
			parent->left_ = nullptr;
		} else {
			std::cerr << "AVL::DeleteLeaf Error: inconsistent state\n";
		}
		size_--; assert(size_ >= 0);
	}
}

int AVL::DeleteMin(std::shared_ptr<AVLNode> currentNode) {
	std::shared_ptr<AVLNode> lastNode = nullptr;
	while (currentNode != nullptr) {
		lastNode = currentNode;
		currentNode = currentNode->left_;
	}
	int result = lastNode->key_;
	std::shared_ptr<AVLNode> parent = lastNode->parent_.lock();
	if (parent == nullptr) {
		// lastNode is root
		if (lastNode->right_ != nullptr) {
			root_ = lastNode->right_;
			lastNode->right_->parent_.reset();
		} else {
			root_ = nullptr;
		}
	} else {
		// lastNode under the root
		if (lastNode->right_ != nullptr) {
			parent->left_ = lastNode->right_;
			lastNode->right_->parent_ = parent;
		} else {
			parent->left_ = nullptr;
		}
  }
	size_--; assert(size_ >= 0);
	return result;
}

size_t AVL::size() const {
	return size_;
}

bool AVL::empty() const {
	return size_ == 0;
}

bool AVL::Find(int key) const {
	std::shared_ptr<AVLNode> currentNode = root_;
	while (currentNode != nullptr) {
		if (currentNode->key_ == key) {
			return true;
		}
		currentNode = (key < currentNode->key_) ?
			currentNode->left_ : currentNode->right_;
	}
	return false;
}

std::string AVL::JSON() const {
	nlohmann::json result;
	std::queue< std::shared_ptr<AVLNode> > nodes;
	if (root_ != nullptr) {
		result["root"] = root_->key_;
		nodes.push(root_);
		while (!nodes.empty()) {
			auto v = nodes.front();
			nodes.pop();
			std::string key = std::to_string(v->key_);
			if (v->left_ != nullptr) {
				result[key]["left"] = v->left_->key_;
				nodes.push(v->left_);
			}
			if (v->right_ != nullptr) {
				result[key]["right"] = v->right_->key_;
				nodes.push(v->right_);
			}
			if (v->parent_.lock() != nullptr) {
				result[key]["parent"] = v->parent_.lock()->key_;
			} else {
				result[key]["root"] = true;
			}
		}
	}
	result["size"] = size_;
	return result.dump(2) + "\n";
}
