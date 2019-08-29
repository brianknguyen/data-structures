#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include "quicksort.h"
#include "mergesort.h"
#include "insertionsort.h"
#include <algorithm>
#include <ctime>

int main(int argc, char **argv){
std::ifstream file;
std::string fname = argv[1];
std::ofstream solution;
solution.open("Solution.csv");
file.open(fname);
nlohmann::json j;
if (file.is_open()) {
    file >> j;
}
    //int arraySize = j["metadata"]["arraySize"];
solution << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl;
std::cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess" << std::endl;

   for (auto itr = j.begin(); itr.key() != "metadata"; ++itr) {
            std::vector <int> temp1;//= new std::vector<int>;//= new std::vector <int>;
            std::vector <int> temp2;
            std::vector <int> temp3;
            int comp = 0;
            int mem = 0;

            for (auto arrayItr = (*itr).begin(); arrayItr != (*itr).end(); ++arrayItr)
            {
                temp1.push_back(*arrayItr);
                temp2.push_back(*arrayItr);
                temp3.push_back(*arrayItr);
            }

            solution << itr.key() << ",";
            std::cout << itr.key() << ",";
            //Insertion:
            clock_t t1;
            t1 = clock();
            InsertionSort(&temp1, &comp, &mem);
            t1 = clock() - t1;
            solution << ((float)t1)/CLOCKS_PER_SEC << ",";
            std::cout << ((float)t1)/CLOCKS_PER_SEC << ",";

            solution << comp << ",";
            solution << mem << ",";
            std::cout << comp << ",";
            std::cout << mem << ",";
            //MergeSort:

            mem = 0;
            comp = 0;

            clock_t t2;
            t2 = clock();
            MergeSort(&temp2, &comp, &mem);
            t2 = clock() - t2;
            solution << ((float)t2)/CLOCKS_PER_SEC << ",";
            std::cout << ((float)t2)/CLOCKS_PER_SEC << ",";

            solution << comp << ",";
            solution << mem << ",";

            std::cout<< comp << ",";
            std::cout << mem << ",";
            //QuickSort

            mem = 0;
            comp = 0;
            clock_t t3;
            t3 = clock();
            QuickSort(&temp3, &comp, &mem);
            t3 = clock() - t3;
            solution << ((float)t3)/CLOCKS_PER_SEC << ",";
            std::cout << ((float)t3)/CLOCKS_PER_SEC << ",";

            solution << comp << ",";
            solution << mem << std::endl;

            std::cout << comp << ",";
            std::cout << mem << std::endl;

           // t1 = ((float)t1)/CLOCKS_PER_SEC;
            //std::cout <<((float)t1)/CLOCKS_PER_SEC << " "<< comp << " " << mem << std::endl;


//            break;


    }

solution.close();
file.close();
//std::cout << jout.dump(2) << std::endl;

}
