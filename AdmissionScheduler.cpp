#include "AdmissionScheduler.h"

void AdmissionScheduler::addJob(int jobIndex)
{
	//Add the index of the given job to the queue.
	_jobQueue.push(jobIndex);
}

queue<int> AdmissionScheduler::checkJobsForAdmission(vector<Job*> jobList, int clockTime)
{
	queue<int> jobs;

	//for each job in the queue
	if (_jobQueue.size())
	{
		Job* job = jobList[_jobQueue.front()];

		// if the jobs arrival time is less than or equal to the current clock time
		// return for admission into memory
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

void AdmissionScheduler::incrementWaiting(queue<int> awaitingMemory)
{
	queue<int> temp;

	//increment items waiting
	while (awaitingMemory.size() > 0)
	{
		int jobIndex = awaitingMemory.front();
		temp.push(jobIndex);
		awaitingMemory.pop();

		Job* job = JobList::getJobs()[jobIndex];

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
