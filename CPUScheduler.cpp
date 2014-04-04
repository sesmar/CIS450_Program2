#include "CPUScheduler.h"

int CPUScheduler::getCurrentClock() { return _clock; }

void CPUScheduler::incrementClock() { _clock++; }

void CPUScheduler::addToReadyQueue(int jobIndex) 
{
	JobList::getJobs()[jobIndex]->setCurrentState("Ready");
   	_readyQueue.push(jobIndex); 
}

int CPUScheduler::queueSize()
{
	int offset = 0;

	if (_running >= 0)
	{
		offset++;
	}

	return _readyQueue.size() + offset;
}

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
				_completed.push(_running);
				_running = -1;
				job->setCompletionTime(_clock);
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

int CPUScheduler::lastCompleted()
{
	int jobIndex = -1;

	if (_completed.size() > 0)
	{
		jobIndex = _completed.front();
		_completed.pop();
	}

	return jobIndex;
}