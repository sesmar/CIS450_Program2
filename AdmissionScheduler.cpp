#include "AdmissionScheduler.h"

void AdmissionScheduler::addJob(int jobIndex)
{
	_jobQueue.push(jobIndex);
}

vector<int> AdmissionScheduler::checkJobsForAdmission(vector<Job*> jobList, int clockTime)
{
	vector<int> jobs;

	Job* job = jobList[_jobQueue.front()];

	while (_jobQueue.size() > 0 && job->getArrivalTime() == clockTime)
	{
		jobs.push_back(_jobQueue.front());
		_jobQueue.pop();

		if (_jobQueue.size() > 0)
		{
			job = jobList[_jobQueue.front()];
		}
	}
	
	return jobs;
}

int AdmissionScheduler::queueSize()
{
	return _jobQueue.size();
}
