#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "insertionsort.cpp"

int main(int argc, char** argv) {
  std::ifstream file;
	std::string file1 = argv[1];
	file.open(file1);
	nlohmann::json jsonObject;

	if (file.is_open()) {
	    file >> jsonObject;
	}

  std::cout << jsonObject.dump(2) << std::endl;
  

}
