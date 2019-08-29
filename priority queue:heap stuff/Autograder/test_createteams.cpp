#include "priorityqueue.cpp"
#include "teamdata.cpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include "teamdata.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

int main()
{
	std::ifstream file;
	std::string file1 = "CreateTeamsExample.json";
	TeamData td(file1);

	//std::cout << td.winPercentages(0,1) << std::endl;

	file.open(file1);
	nlohmann::json j1;
	if (file.is_open()) {
	    file >> j1;
	}
	int numPlayers = j1["metadata"]["numPlayers"];
	size_t factorial1 = 1;
	size_t factorial2 = 1;

    for(size_t i = 1; i <=numPlayers; ++i)
    {
        factorial1 *= i;
    }
    for(size_t i = 1; i <=numPlayers-2; ++i)
    {
        factorial2 *= i;
    }

    size_t maxnodes = ((factorial1)/(2*factorial2));
    //std::cout << maxnodes << std::endl;
    PriorityQueue p(maxnodes);

	for (int i = 0; i < numPlayers -1; i++)
    {
        for (int j = i+1; j < numPlayers; j++)
        {
            double key = fabs(td.winPercentages(i,j) - 50);
            p.insert(std::make_pair(key,std::make_pair(i, j)));
           // std::cout << key<< std::endl;
        }

    }
    //nlohmann::json jout;
   // nlohmann::json* jteams; //= jout["teams"];

     nlohmann::json jout; //= new nlohmann::json [1];
     std::vector<Value> teams;

    KeyValuePair rmin;

    for (int i = 1; i<= numPlayers/2; i ++)
    {
        rmin = p.removeMin();

        teams.push_back(rmin.second);
        //break;
    }
   jout["teams"] = teams;

    std::cout << jout.dump(2) << std::endl;

    file.close();
    //PriorityQueue P(0);

}

