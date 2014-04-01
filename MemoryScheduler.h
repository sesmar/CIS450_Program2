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
		MemoryScheduler();
		//function declarations
		void FirstFit(char ProcessID, int memNeeded);
		void WorstFit(char ProcessID, int memNeeded);
		void BestFit(char ProcessID, int memNeeded);
		void ReleaseMemory(char ProcessID);
		vector<char> getMemory();
};



#endif /* End MEMSCHED_H */
