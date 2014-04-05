#include "AdmissionScheduler.h"

void AdmissionScheduler::addJob(int jobIndex)
{
	_jobQueue.push(jobIndex);
}

queue<int> AdmissionScheduler::checkJobsForAdmission(vector<Job*> jobList, int clockTime)
{
	queue<int> jobs;

	if (_jobQueue.size())
	{
		Job* job = jobList[_jobQueue.front()];

		while (_jobQueue.size() > 0 && job->getArrivalTime() <= clockTime)
		{
			jobs.push(_jobQueue.front());
			_jobQueue.pop();

			if (_jobQueue.size() > 0)
			{
				job = jobList[_jobQueue.front()];
			}
		}
	}

	return jobs;
}

void AdmissionScheduler::incrementWaiting(queue<int> awaitingMemory, int clockTime)
{
	queue<int> temp;

	//increment items waiting
	while (awaitingMemory.size() > 0)
	{
		int jobIndex = awaitingMemory.front();
		temp.push(jobIndex);
		awaitingMemory.pop();

		Job* job = JobList::getJobs()[jobIndex];

		if (clockTime > job->getArrivalTime())
		job->incrementWaitingTime();
	}

	while (temp.size() > 0)
	{
		int jobIndex = temp.front();
		awaitingMemory.push(jobIndex);
		temp.pop();
	}
}

int AdmissionScheduler::queueSize()
{
	return _jobQueue.size();
}
