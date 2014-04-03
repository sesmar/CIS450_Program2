#include "CPUScheduler.h"

int CPUScheduler::getCurrentClock() { return _clock; }

void CPUScheduler::incrementClock() { _clock++; }

void CPUScheduler::addToReadyQueue(int jobIndex) { _readyQueue.push(jobIndex); }

bool CPUScheduler::isTimeup()
{
	if (_running ==  -1)
	{
		return true;
	}

	return true;
}

void CPUScheduler::scheduleJob()
{
	if (isTimeup())
	{
		if (_running >= 0)
		{
			Job* job = JobList::getJobs()[_running];
			job->incrementRunningTime();

			if (job->getServiceTime() == job->getRunningTime())
			{
				job->setCurrentState("Done");
			}
			else
			{
				job->setCurrentState("Ready");
			}
		}

		incrementReady();

		if (_readyQueue.size() > 0)
		{
			if (_running > -1)
			{
				_readyQueue.push(_running);
			}

			_running = _readyQueue.front();
			Job* job = JobList::getJobs()[_running];
			job->setCurrentState("Running");

			_readyQueue.pop();
		}
		else
		{
			_running = -1;
		}
	}
}

void CPUScheduler::incrementReady()
{
	queue<int> temp;

	while (_readyQueue.size() > 0)
	{
		int jobIndex = _readyQueue.front();
		temp.push(jobIndex);
		_readyQueue.pop();

		Job* job = JobList::getJobs()[jobIndex];
		job->incrementReadyTime();
	}

	while (temp.size() > 0)
	{
		int jobIndex = temp.front();
		_readyQueue.push(jobIndex);
		temp.pop();
	}
}