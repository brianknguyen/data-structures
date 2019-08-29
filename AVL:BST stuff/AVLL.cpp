#include <cassert>
#include <iostream>
#include <string>
#include <queue>
#include "AVLL.h"
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

void AVL::rightRotate(std::shared_ptr<AVLNode> a){

    if (a == root_)
    {
        std::cout <<"root" << std::endl;
        std::shared_ptr<AVLNode> b = a->left_;
        std::shared_ptr<AVLNode> c = b->left_;
        root_ = std::make_shared<AVLNode>(b->key_);
        root_->left_=b->left_;
        root_->right_=b->right_;

        if(root_->HasRightChild())
       {
        a->left_=root_->right_;

        }
        else{
            root_->left_ = nullptr;
        }

        root_->right_ = a;
        a->parent_ = root_;

       // root_->right_ = a;
       // a->parent_ = root_;

        updateHeight(a);

        updateHeight(root_);


    }

    else {



        std::shared_ptr<AVLNode> u = a->parent_.lock();
        //std::cout <<"ran" << std::endl;

        bool isLeft = (u->left_ == a);
        //std::cout <<"ran" << std::endl;


        std::shared_ptr<AVLNode> b = a->left_;
        //std::cout <<"ran" << std::endl;

        std::shared_ptr<AVLNode> c = b ->left_;
        //std::cout <<"ran" << std::endl;
        if(b->HasRightChild()){
        a->left_ = b->right_;
         }
         else{
            a->left_ = nullptr;
         }

        //if(b->right_ != nullptr){
        b->right_ = a;
        a->parent_ = b;
        //}

        /*if(b->right_ != nullptr)
        {
            b->right_ ->parent_= a;
        }*/

        if(isLeft)
        {
            u->left_=b;
            b->parent_ =u;
        }
        else
        {
            u->right_=b;
            b->parent_=u;
        }
        updateHeight(a);
        updateHeight(b);
       // std::cout << c->height << std::endl;
       // updateHeight(c);
        //std::cout << c->height << std::endl;

        updateHeight(u);
        std::shared_ptr<AVLNode> p = u->parent_.lock();
        while (p!= nullptr)
        {
            updateHeight(p);
            p = p->parent_.lock();
        }

    }



}

void AVL::leftRotate(std::shared_ptr<AVLNode> a){

    if (a == root_)
    {
        std::cout <<"root" << std::endl;
        std::shared_ptr<AVLNode> b = a->right_;
        std::shared_ptr<AVLNode> c = b->right_;
        root_ = std::make_shared<AVLNode>(b->key_);
        root_->left_=b->left_;
        root_->right_=b->right_;

        a->right_=root_->left_;

      //  if(root_->left_!= nullptr)
       // {
        root_->left_ = a;
        a->parent_ = root_;
       // }
        //root_->left_ = a;
        //a->parent_ = root_;
        //b->left_ = root_->right_;

      //  if(root_->right_ != nullptr)
       // {
         //   root_->right_->parent_=b;
     //   }
       // root_->right_ = b;
       // b->parent_ = root_;
        updateHeight(a);

        updateHeight(root_);
        //updateHeight(root_);

    }

    else {
     //   std::cout <<"else" << std::endl;



        std::shared_ptr<AVLNode> u = a->parent_.lock();
        //std::cout <<"ran" << std::endl;

        bool isLeft = (u->left_ == a);
        //std::cout <<"ran" << std::endl;


        std::shared_ptr<AVLNode> b = a->right_;
       // std::cout <<"ran" << std::endl;

        std::shared_ptr<AVLNode> c = b ->right_;
       // std::cout <<"ran" << std::endl;
        if (b->left_ !=nullptr)
        {



        a->right_ = b->left_;
        }
      //  if(b->left_ != nullptr){
        b->left_ = a;
        a->parent_ = b;
       // }
        /*b->left_ = c->right_;
        if(c->right_ != nullptr)
        {
            c->right_->parent_ = b;
        }
        c->left_ =a;
        a->parent_=c;

        c->right_=b;
        b->parent_=c;
            */
        if(isLeft)
        {
            u->left_=b;
            b->parent_ =u;
        }
        else
        {
            u->right_=b;
            b->parent_=u;
        }
        updateHeight(a);
        updateHeight(b);
       // std::cout << c->height << std::endl;
       // updateHeight(c);
        //std::cout << c->height << std::endl;

        updateHeight(u);
        std::shared_ptr<AVLNode> p = u->parent_.lock();
        while (p!= nullptr)
        {
            updateHeight(p);
            p = p->parent_.lock();
        }

    }




}
void AVL::rightleftRotate(std::shared_ptr<AVLNode> a) {
  //  std::cout <<"ran" << std::endl;
    if (a == root_)
    {
      //  std::cout <<"root" << std::endl;
        std::shared_ptr<AVLNode> b = a->right_;
        std::shared_ptr<AVLNode> c = b->left_;
        root_ = std::make_shared<AVLNode>(c->key_);
        root_->left_=c->left_;
        root_->right_=c->right_;

        a->right_=root_->left_;

        if(root_->left_!= nullptr)
        {
            root_->left_->parent_ = a;
        }
        b->left_ = root_->right_;

        if(root_->right_ != nullptr)
        {
            root_->right_->parent_=b;
        }
        root_->right_ = b;
        b->parent_ = root_;
        updateHeight(a);
        updateHeight(b);
        updateHeight(root_);

    }

    else {
           //     std::cout <<"else" << std::endl;
        std::shared_ptr<AVLNode> u = a->parent_.lock();
        bool isLeft = (u->left_ == a);

        std::shared_ptr<AVLNode> b = a->right_;
        //std::cout <<"ran" << std::endl;

        std::shared_ptr<AVLNode> c = b ->left_;
        //std::cout <<"ran" << std::endl;

        a->right_ = c->left_;

        if(c->left_ != nullptr)
        {
            c->left_->parent_ = a;
        }
        b->left_ = c->right_;
        if(c->right_ != nullptr)
        {
            c->right_->parent_ = b;
        }
        c->left_ =a;
        a->parent_=c;

        c->right_=b;
        b->parent_=c;

        if(isLeft)
        {
            u->left_=c;
            c->parent_ =u;
        }
        else
        {
            u->right_=c;
            c->parent_=u;
        }
        updateHeight(a);
        updateHeight(b);
        updateHeight(c);
        updateHeight(u);

        std::shared_ptr<AVLNode> p = u->parent_.lock();
        while (p!= nullptr)
        {
            updateHeight(p);
            p = p->parent_.lock();
        }


    }

}

void AVL::leftrightRotate(std::shared_ptr<AVLNode> a) {
    if (a == root_)
    {
        //std::cout <<"ran" << std::endl;
        std::shared_ptr<AVLNode> b = a->left_;
        std::shared_ptr<AVLNode> c = b->right_;
        root_ = std::make_shared<AVLNode>(c->key_);

        root_->left_=c->left_;
        root_->right_=c->right_;
        a->left_=root_->right_;

        if(root_->right_!= nullptr)
        {
            root_->right_->parent_ = a;
        }
        b->right_ = root_->left_;

        if(root_->left_ != nullptr)
        {
            root_->left_->parent_=b;
        }
        root_->left_ = b;
        b->parent_ = root_;
        updateHeight(a);
        updateHeight(b);
        updateHeight(root_);
    }

    else {
        //std::cout <<"ran" << std::endl;

        std::shared_ptr<AVLNode> u = a->parent_.lock();
        bool isLeft = (u->left_ == a);

        std::shared_ptr<AVLNode> b = a->left_;
        std::shared_ptr<AVLNode> c = b ->right_;
        a->left_ = c->right_;

        if(c->right_!= nullptr)
        {
            c->right_->parent_ = a;
        }
        b->right_ = c->left_;
        if(c->left_!= nullptr)
        {
            c->left_->parent_ = b;
        }
        c->right_ =a;
        a->parent_=c;

        c->left_=b;
        b->parent_=c;

        if(isLeft)
        {
            u->left_=c;
            c->parent_ =u;
        }
        else
        {
            u->right_=c;
            c->parent_=u;
        }
        updateHeight(a);
        updateHeight(b);
        updateHeight(c);
        updateHeight(u);
        std::shared_ptr<AVLNode> p = u->parent_.lock();
        while (p!= nullptr)
        {
            updateHeight(p);
            p = p->parent_.lock();
        }
    }



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
    bool rightchild;
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
        //parent = lastNode->left_->parent_.lock();
		while (parent != nullptr)
        {
            updateHeight(parent);
              //  std::cout << parent->balance << std::endl;

            parent = parent->parent_.lock();
          //  std::cout <<
        }

	//	lastNode->height = 1 + std::max(lastNode->left_->height, lastNode->right->height);

	} else {
	    rightchild = true;
		lastNode->right_ = std::make_shared<AVLNode>(key, lastNode);
        lastNode->right_->height = 0;
        lastNode->right_->balance = 0;
        parent = lastNode->right_->parent_.lock();
        while (parent != nullptr)
        {
            updateHeight(parent);
                        //    std::cout << parent->balance << std::endl;

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

                            std:: cout << "leftrightrotate "<<std::endl;
                           leftrightRotate(parentbalance);
                           break;

                    }
                }
                else
                {
                        std:: cout << "rightrotate "<<std::endl;
                        rightRotate(parentbalance);
                        break;
                }
            }

            // Right Left Case
            if (parentbalance->balance < -1){//&& parentbalance->right_->HasLeftChild()){
                if (parentbalance->right_->HasLeftChild())
                {
                    if (parentbalance->right_->balance == 1)
                    {
                          // std:: cout << "--" <<std::endl;
                    std:: cout << "rightleftrotate "<<std::endl;

                        rightleftRotate(parentbalance);
                        break;

                    }
                }
                else {
                //if (parentbalance->right_->HasRightChild())
                //{
                    std:: cout << "leftrotate "<<std::endl;
                    //leftRotate(parentbalance);
                    break;
                }
               // }
            }
            //updateHeight(parentbalance);
            parentbalance = parentbalance->parent_.lock();

        }



    //int balance = lastNode->left_->height - lastNode->right_->height;
     // Left Left Case
 //    std::cout << balance << std::endl;
//     std::shared_ptr<AVLNode> tempnode;

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
