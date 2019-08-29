#include "priorityqueue.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "teamdata.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

int main(int argc, char **argv)
{
	std::ifstream file;
	std::string file1 = argv[1];
	TeamData td(file1);


	file.open(file1);
	nlohmann::json j1;
	if (file.is_open()) {
	    file >> j1;
	}
	int numPlayers = j1["metadata"]["numPlayers"];

    size_t res = 1;

    for (int k = 1; k <= 2; ++k)
    {
        res *= numPlayers - k + 1;
        res /= k;
    }


    PriorityQueue p(res);

	for (int i = 0; i < numPlayers-1; i++) {
       	 for (int j = i+1; j < numPlayers; j++) {
            double key = fabs(td.winPercentages(i,j) - 50);
            p.insert(std::make_pair(key,std::make_pair(i, j)));
	 }

        }


     nlohmann::json jout;
     std::vector<Value> teams;

    KeyValuePair rmin;

    for (int i = 1; i<= numPlayers/2; i ++)
    {
        rmin = p.removeMin();
        teams.push_back(rmin.second);
        p.remove_team(rmin.second);

    }
    jout["teams"] = teams;

    std::cout << jout.dump(2)<< std::endl;
    file.close();

}
