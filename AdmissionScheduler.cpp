#include "AdmissionScheduler.h"

void AdmissionScheduler::addJob(Job job)
{
	_jobQueue.push(job);
}

vector<Job> AdmissionScheduler::checkJobsForAdmission(int clockTime)
{
	vector<Job> jobs;

	Job job = _jobQueue.front();

	while (job.getArrivalTime() == clockTime)
	{
		jobs.push_back(job);
		_jobQueue.pop();
		job = _jobQueue.front();
	}
	
	return jobs;
}

int AdmissionScheduler::queueSize()
{
	return _jobQueue.size();
}
