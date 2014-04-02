#include <iostream>
#include <vector>

using namespace std;


#ifndef MEMSCHED_H
#define MEMSCHED_H

class MemoryScheduler
{
	protected:
		vector<char> _memory;

	public:
		MemoryScheduler();

		virtual bool scheduleJob(char processId, int memNeeded) = 0;

		void releaseMemory(char processId);
		vector<char> getMemory();
};

class FirstFitMemoryScheduler : public MemoryScheduler
{
public:
	virtual bool scheduleJob(char processId, int memNeeded);
};

class WorstFitMemoryScheduler : public MemoryScheduler
{
public:
	virtual bool scheduleJob(char processId, int memNeeded);
};

class BestFitMemoryScheduler : public MemoryScheduler
{
public:
	virtual bool scheduleJob(char processId, int memNeeded);
};

#endif /* End MEMSCHED_H */
