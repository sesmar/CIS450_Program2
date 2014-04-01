#include <iostream>
#include <vector>

using namespace std;


#ifndef MEMSCHED_H
#define MEMSCHED_H

class MemoryScheduler
{
	private:

		vector<char> _memory;   //vector <char> memory (256,'_');     <<must be intialized to size 256 with '_' characters

	public:
			//function declarations
			void FirstFit(vector<char> &memory, char ProcessID, int memNeeded);
			void WorstFit(vector<char> &memory, char ProcessID, int memNeeded);
			void BestFit(vector<char> &memory, char ProcessID, int memNeeded);
			void ReleaseMemory(vector<char> &memory, char ProcessID);
};



#endif /* End MEMSCHED_H */
