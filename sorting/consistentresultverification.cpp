#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

nlohmann::json consistentResultVer(nlohmann::json j1, nlohmann::json j2, std::string file1, std::string file2) {
	nlohmann::json jsonObject;
	int arraySize1 = j1["metadata"]["arraySize"];
	int arraySize2 = j2["metadata"]["arraySize"];
	int num_mismatchsamples = 0;



	for (auto itr1 = j1.begin(); itr1 != j1.end(); ++itr1) {
		int num_mismatches = 0;
		bool mismatches_exist = false;

			//std::cout <<"key: "<< itr.key() << "value: " << itr.value() << std::endl;
			nlohmann::json itr2 = j2[itr1.key()];
			if (itr1.key() != "metadata") {
				std::vector <int> temp1;
				std::vector<int> temp2;

				//std::cout << "key: " << itr.key() << "value: " << itr.value() << std::endl;
				for (auto arrayItr1 = (*itr1).begin(); arrayItr1 != (*itr1).end(); ++arrayItr1) {
					temp1.push_back(*arrayItr1);
				}
				for (auto arrayItr2 = (itr2).begin(); arrayItr2 != (itr2).end(); ++arrayItr2) {
					temp2.push_back(*arrayItr2);
				}
				std::vector<int> temp3;
				for (int i = 0; i < arraySize1; ++i) {
					if (temp1[i] != temp2[i]) {
						num_mismatches++;
						mismatches_exist = true;
						jsonObject[itr1.key()]["Mismatches"][std::to_string(num_mismatches)] = {temp1[i], temp2[i]};
					}
				}
				if (mismatches_exist) {
					++num_mismatchsamples;
					jsonObject[itr1.key()][file1] = temp1;
					jsonObject[itr1.key()][file2] = temp2;

				}

			}
			else {
				jsonObject["metadata"]["File1"] = (*itr1);
				jsonObject["metadata"]["File1"]["name"] = file1;
				jsonObject["metadata"]["File2"] = itr2;
				jsonObject["metadata"]["File2"]["name"] = file2;

				jsonObject["metadata"]["samplesWithConflictingResults"] = num_mismatchsamples;
			}

	}

return jsonObject;
}





int main(int argc, char** argv) {
	std::ifstream file;
	std::ifstream otherfile;
	std::string file1 = "SampleExample.json";
  std::string file2 = "AlmostSampleExample.json";
	file.open(file1);
	otherfile.open(file2);
	nlohmann::json jsonObject1;
	nlohmann::json jsonObject2;
	nlohmann::json joutput;


	if (file.is_open()) {
	    file >> jsonObject1;
	}

	if (otherfile.is_open()) {
		otherfile >> jsonObject2;
	}

	joutput = consistentResultVer(jsonObject1, jsonObject2, file1, file2);
	std::cout << joutput.dump(2) << std::endl;

}
