#include "priorityqueue.cpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {

	std::ifstream file;
	std::string fname = argv[1];
	file.open(fname);
	nlohmann::json j1;
	PriorityQueue P(4);
	nlohmann::json jout;
	int numOperations = 0;
	int maxheap;
	if (file.is_open()) {
	    file >> j1;
	}
	    file.close();
for (auto itr1 = j1.begin(); itr1 != j1.end(); ++itr1) {
    if (itr1.key() == "metadata") {
        maxheap = (*itr1)["maxHeapSize"];
    }

}
        	PriorityQueue P(maxheap);

    for (auto itr1 = j1.begin(); itr1 != j1.end(); ++itr1) {
        if (itr1.key() != "metadata") {
                if ((*itr1)["operation"] == "insert")
                {
                double key = j1[itr1.key()]["key"];

                P.insert(key);

                }
                if ((*itr1)["operation"] == "removeMin")
                {
                    KeyValuePair rmin = P.removeMin();
                }
                ++numOperations;
        }
        else {
            jout = P.JSON();
            jout["metadata"]["numOperations"] = numOperations;
        }
    }

    std::cout << jout.dump(2) << std::endl;

    //PriorityQueue P(0);

}

