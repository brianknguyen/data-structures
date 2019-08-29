void AVL::rightleft(std::shared_ptr<AVLNode> lastNode) {
  //  std::cout <<"ran" << std::endl;
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
