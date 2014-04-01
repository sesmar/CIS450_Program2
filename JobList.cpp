#include "JobList.h"

vector<Job>* JobList::_jobs = new vector<Job>();

vector<Job> JobList::getJobs()
{
	vector<Job> jobs;

	for(int i = 0; i < _jobs->size(); i++)
	{
		Job job = _jobs->at(i);
		jobs.push_back(job);
	}


	return jobs;
}

void JobList::addJob(Job job)
{
	_jobs->push_back(job);
}
