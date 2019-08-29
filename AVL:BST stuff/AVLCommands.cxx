#include <cassert>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>

#include "AVLL.cpp"


int main(int argc, char **argv) {

    std::ifstream file;
    std::string fname = argv[1];
    file.open(fname);
    nlohmann::json j1;
    nlohmann::json jout;
    int maxheap;
    if (file.is_open()) {
        file >> j1;
    }
        file.close();

    AVL B;
	nlohmann::json result;
    std::queue< std::shared_ptr<AVLNode> > nodes;


    for (auto itr1 = j1.begin(); itr1 != j1.end(); ++itr1) {
        if (itr1.key() != "metadata") {
                if ((*itr1)["operation"] == "Insert")
                {
                int key = j1[itr1.key()]["key"];

                B.Insert(key);

                }
                /*if ((*itr1)["operation"] == "Delete")
                {
                    int key = j1[itr1.key()]["key"];
                    B.Delete(key);
                }
                 if ((*itr1)["operation"] == "DeleteMin")
                {
                    B.DeleteMin();
                }*/
        }
    }
	if (B.root_ != nullptr) {
        result["height"] = B.root_->height;
		result["root"] = B.root_->key_;
		nodes.push(B.root_);
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
            result[key]["height"] = v->height;
            result[key]["balance factor"] = -v->balance;
            result["size"] = B.size_;
		}
	}


    std::cout << result.dump(2) << std::endl;
    return 0;

}
