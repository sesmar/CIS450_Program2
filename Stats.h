#include <iostream>
#include <vector>
#include "Job.h"

using namespace std;

#ifndef STATS_H
#define STATS_H

class Stats
{
	private:

			vector<float> _percentHoleData;       //used to store each hole calculation so an average can be computed at the end
	

	public:
			Stats() { }
			void OutputMem(vector<char> memory);       //call this function to print memory statistics
			void MemMap(vector<char> memory);          //prints memory map
			void PercentHoles(vector<char> memory);    //prints percentage of holes in memory map
			void ProcessStates(vector<Job*> Jobs, int clockTime);      //prints out information for each process

			void logHolePercent(float percentHole);   //called after every percent hole calculation to store the hole percentages        
			void getAvgHolePercent();    //call at the end of the main program to compute average for every process logged
			float getAvgWaitTime(vector<Job*> Jobs);                   //call at the end of the main program to compute average for every process logged

};

#endif /* End STATS_H */
