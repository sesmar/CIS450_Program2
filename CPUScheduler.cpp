#include "CPUScheduler.h"

int CPUScheduler::getCurrentClock() { return _clock; }

void CPUScheduler::incrementClock() { _clock++; }

void CPUScheduler::addToReadyQueue(int jobIndex) 
{
	JobList::getJobs()[jobIndex]->setCurrentState("Ready");
	_next = jobIndex;
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
	bool returnValue = true;

	if (_running ==  -1)
	{
		returnValue = true;
	}

	return returnValue;
}

void CPUScheduler::scheduleJob()
{
	if (isTimeup())
	{
		if (_running >= 0)
		{
			Job* job = JobList::getJobs()[_running];

			job->setCurrentState("Ready");
		}

		if (_readyQueue.size() > 0 || _next > -1)
		{
			if (_running > -1)
			{
				_readyQueue.push(_running);
			}

			if (_next > -1)
			{
				_running = _next;
				_next = -1;
			}
			else
			{
				_running = _readyQueue.front();
				_readyQueue.pop();
			}

			Job* job = JobList::getJobs()[_running];
			job->setCurrentState("Running");
			job->incrementRunningTime();

			if (job->getServiceTime() == job->getRunningTime())
			{
				job->setCurrentState("Done");
				_completed.push(_running);
				_running = -1;
				job->setCompletionTime(_clock);
			}
		}
		else
		{
			_running = -1;
		}

		incrementReady();
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