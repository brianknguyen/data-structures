
#include <iostream>
#include "json.hpp"
#include "teamdata.h"
#include <fstream>

TeamData::TeamData(std::string filename) {
    std::ifstream file;
	file.open(filename);
	nlohmann::json j1;

	int counter = 0;
	if (file.is_open()) {
	    file >> j1;
	}
	    file.close();
    numPlayers_ = j1["metadata"]["numPlayers"];
    winPercentages_ = new double*[numPlayers_];
    for(int i = 0; i < numPlayers_; ++i){
            winPercentages_[i] = new double[numPlayers_];
    }
    for (auto itr1 = j1.begin(); itr1 != j1.end(); ++itr1) {
            if (itr1.key() == "teamStats") {
                nlohmann::json j2 = (*itr1);
                for (int k = 0; k != j2.size(); k++) {
                    int i = j2[k]["playerOne"];
                    int j = j2[k]["playerTwo"];
                    winPercentages_[i][j] = j2[k]["winPercentage"];
                    winPercentages_[j][i] = j2[k]["winPercentage"];
                }
            }

    }
}



int TeamData::numPlayers() const
{
    return numPlayers_;
}
