#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
nlohmann::json sortedver(nlohmann::json j, std::string fname)
{
    nlohmann::json jout;
    //int sample1vec = j["Sample1"];
    //int sample2vec = j["Sample2"];
    int arraySize = j["metadata"]["arraySize"];
    int sample_w_inversions = 0;
    //bool inversion_exists = false;
    for (auto itr = j.begin(); itr != j.end(); ++itr) {
        //std::cout <<"key: "<< itr.key() << "value: " << itr.value() << std::endl;
        bool inversion_exists = false;
        if (itr.key() != "metadata") {
            std::vector <int> temp;
            //int inversions_found = 0 ;
            for (auto arrayItr = (*itr).begin(); arrayItr != (*itr).end(); ++arrayItr)
            {
                temp.push_back(*arrayItr);
            }
            for (int i = 0; i < arraySize -1 ; ++i) {
                if (temp[i] >= temp[i+1])
                {
                    inversion_exists = true;
                    //++inversions_found;
                    //std::vector <int> found = {1,2};
                    //jout.push_back(nlohmann::json::object_t::value_type(itr.key(), "ConsecutiveInversions: "));
                   // jout[itr.key()].push_back(nlohmann::json::object_t::value_type("ConsecutiveInversions: ", 1 ));
                   jout[itr.key()]["ConsecutiveInversions"][std::to_string(i)] = {temp[i], temp[i+1]};
                   //jout[itr.key()]["ConsecutiveInversions"].push_back(nlohmann::json::object_t::value_type(std::to_string(inversions_found), temp[i+1] ));
                   //jout[itr.key()].push_back(nlohmann::json::object_t::value_type("ConsecutiveInversions: ", 2 ));

                }
            }
            if (inversion_exists)
            {
                ++sample_w_inversions;

                jout[itr.key()]["sample"] = itr.value();
                //++sample_w_inversions;
            }


        }
        else {
        jout.push_back(nlohmann::json::object_t::value_type(itr.key(), itr.value()));
        //jout["metadata"] = itr.value;
        jout["metadata"]["file"] = fname;
        jout["metadata"]["samplesWithInversions"] = sample_w_inversions;
        }

        //sample ++;
    }

    //jout.push_back(nlohmann::json::object_t::value_type(j["metadata"].key(), j["metadata"].value()));
    return jout;
}

int main(){
std::ifstream file;
std::string fname = "../Examples/Example100.json";
file.open(fname);
nlohmann::json jsonObject;
nlohmann::json joutput;
if (file.is_open()) {
    file >> jsonObject;
}
//std::cout << jsonObject.dump(2) << std::endl;
joutput = sortedver(jsonObject,fname);
//std::cout << jsonObject["metadata"] << std::endl;
std::cout << joutput.dump(2) << std::endl;

}
