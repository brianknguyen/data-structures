#include <cassert>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "BST.h"
#include "BST.cpp"
#include "AVL.h"
#include "AVL.cpp"


int main() {

    std::ifstream file;
    std::string fname = "TestCase1.AVLCommands.json";
    file.open(fname);
    nlohmann::json j1;
    nlohmann::json jout;
    int maxheap;
    if (file.is_open()) {
        file >> j1;
    }
        file.close();

    AVL B;

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



    std::cout << B.JSON() << std::endl;


}
