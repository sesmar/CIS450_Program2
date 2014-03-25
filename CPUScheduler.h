#include <queue>
#include "Job.h"

#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H

class CPUScheduler
{
	private:
		int _clock;
		queue<Job> _readyQueue;
		//Job _running;

	public:
		CPUScheduler() { _clock = 0; }
		int getCurrentClock();
		int incrementClock();
		void addToReadyQueue(Job job);
};

#endif /*CPUSCHEDULER*/
