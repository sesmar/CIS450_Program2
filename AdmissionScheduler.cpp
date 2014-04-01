#include "AdmissionScheduler.h"

void AdmissionScheduler::addJob(int jobIndex)
{
	_jobQueue.push(jobIndex);
}

vector<Job> AdmissionScheduler::checkJobsForAdmission(vector<Job> jobList, int clockTime)
{
	vector<Job> jobs;

	Job job = jobList[_jobQueue.front()];

	while (job.getArrivalTime() == clockTime)
	{
		jobs.push_back(job);
		_jobQueue.pop();
		job = jobList[_jobQueue.front()];
	}
	
	return jobs;
}

int AdmissionScheduler::queueSize()
{
	return _jobQueue.size();
}
