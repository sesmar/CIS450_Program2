#include <queue>
#include "Job.h"
#include "JobList.h"

#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H

class CPUScheduler
{
	private:
		int _clock;
		queue<int> _readyQueue;
		queue<int> _completed;
		int _running;
		int _next;
		int _quantum;
		bool isTimeup();
		void incrementReady();

	public:
		CPUScheduler() { _clock = 0; _running = -1; _next = -1; _quantum = 1; }
		int getCurrentClock();
		void incrementClock();
		void addToReadyQueue(int jobIndex);

		void scheduleJob();
		int queueSize();
		int lastCompleted();
};

#endif /*CPUSCHEDULER*/
